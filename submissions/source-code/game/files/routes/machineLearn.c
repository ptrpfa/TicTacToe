#include <gtk/gtk.h>                // Include GTK library for GUI
#include "../header/config.h"       // Include configuration file

//Global Var
int board_features[NO_FEATURES];                                        // Array containing the feature values for the current board state
float model_weights[NO_FEATURES] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0}; // Array containing weights for each feature
int possible_moves[BOARDSIZE][BOARDSIZE + 1];                           // 2D array containing possible moves for model to choose from (last element of each inner array represents the move)                                        
float learningRate = 0.001; 

/* Machine Learning Model Functions */
// Function to read the ML model's weights from the settings file                                                                    
void readWeights() {
    // Initialise file pointer for reading
    FILE * settings_file = fopen(SETTINGS_FILE, "r");
    int index = 0;
    float value = 0;
    // Check if file pointer is valid
    if (settings_file == NULL){
        printf("%s does not exist!\n", SETTINGS_FILE);
        exit(1);
    }
    // Read file contents
    for (int i = 0; i < NO_FEATURES; i++) {
        // Read current line in the file
        fscanf(settings_file, "w%d = %f\n", &index, &value);
        // Update ML model's weights
        model_weights[index] = value;
    }
    // Close file pointer
    fclose(settings_file);
}     

// Function to get the feature values for the current board's state
void getBoardFeatures(int gameState[BOARDSIZE], int playerNo) {
    /* 
        Board features (x0 to x6):
        x0: Constant value of 1
        x1: Number of rows, columns and diagonals with 2 of the selected player's pieces and 1 empty cell
        x2: Number of rows, columns and diagonals with 2 of the opposing player's pieces and 1 empty cell
        x3: Number of the selected player's pieces in the center cell (Indicates if the selected player's piece is in the center cell or not, 0 or 1)
        x4: Number of the selected player's pieces that are in the corner cells (0 to 4)
        x5: Number of rows, columns and diagonals with 1 of the selected player's piece and 2 empty cells
        x6: Number of rows, columns and diagonals with 3 of the selected player's pieces (win detection)
    */
    // Initialise feature values
    int x0 = 1, x1 = 0, x2 = 0, x3 = 0, x4 = 0, x5 = 0, x6 = 0;
    // Create a 2D array from the current board's state
    int current_board[3][3];
    current_board[0][0] = gameState[0];
    current_board[0][1] = gameState[1];
    current_board[0][2] = gameState[2];
    current_board[1][0] = gameState[3];
    current_board[1][1] = gameState[4];
    current_board[1][2] = gameState[5];
    current_board[2][0] = gameState[6];
    current_board[2][1] = gameState[7];
    current_board[2][2] = gameState[8];
    // Loop through each board row
    for (int row = 0; row < 3; row++) {
        // Initialise counter variables
        int row_empty = 0, row_player = 0, row_oppose = 0, col_empty = 0, col_player = 0, col_oppose = 0;
        // Loop through each board column
        for (int col = 0; col < 3; col++) {
            // Obtain row counts
            if (current_board[row][col] == playerNo) {
                row_player++;
            }
            else if (current_board[row][col] == 0) {
                row_empty++;
            }
            else {
                row_oppose++;
            }
            // Obtain column counts
            if (current_board[col][row] == playerNo) {
                col_player++;
            }
            else if (current_board[col][row] == 0) {
                col_empty++;
            }
            else {
                col_oppose++;
            }
            // Check x3 and x4 conditions
            if (row == col) { // Check top-right to bottom-left diagonal
                if (row == 1 && col == 1) {
                    // Checking for center piece
                    if (current_board[row][col] == playerNo){
                        x3++;
                    }
                }
                else {
                    // Checking for corner piece
                    if (current_board[row][col] == playerNo){
                        x4++;
                    }
                }
            }
            if ((row + col) == 2) { // Check bottom-left to top-right diagonal
                if (row != 1 && col != 1) {
                    // Checking for corner piece
                    if (current_board[row][col] == playerNo){
                        x4++;
                    }
                }
            }
            // Check for x1 conditions
            if (row_player == 2 && row_empty == 1) {
                x1++;
            }
            if (col_player == 2 && col_empty == 1) {
                x1++;
            }
            // Check for x2 conditions
            if (row_oppose == 2 && row_empty == 1) {
                x2++;
            }
            if (col_oppose == 2 && col_empty == 1) {
                x2++;
            }
            // Check for x5 conditions
            if (row_player == 1 && row_empty == 2) {
                x5++;
            }
            if (col_player == 1 && col_empty == 2) {
                x5++;
            }
            // Check for x6 conditions
            if (row_player == 3) {
                x6++;
            }
            if (col_player == 3) {
                x6++;
            }
        }
    }
    // Loop to check diagonals
    for (int i = 0; i < 2; i++) {
        // Initialise counter variables
        int diagonal_empty = 0, diagonal_player = 0, diagonal_oppose = 0, temp_value = 0;
        for (int j = 0; j < 3; j++) { 
            // Set temporary value for comparison
            if (i == 0) {
                // Check bottom-left to top-right diagonal
                temp_value = current_board[2 - j][j];
            }
            else {
                // Check top-left to bottom-right diagonal
                temp_value = current_board[j][j];
            }
            // Check diagonals
            if (temp_value == playerNo) {
                diagonal_player++;
            }
            else if (temp_value == 0) {
                diagonal_empty++;
            }
            else {
                diagonal_oppose++;
            }
        }
        // Check for x1, x2, x5 and x6 conditions
        if (diagonal_player == 2 && diagonal_empty == 1) {
            x1++;
        }
        if (diagonal_oppose == 2 && diagonal_empty == 1) {
            x2++;
        }
        if (diagonal_player == 1 && diagonal_empty == 2) {
            x5++;
        }
        if (diagonal_player == 3) {
            x6++;
        }
    }
    // Set values of the current board's features
    board_features[0] = x0;
    board_features[1] = x1;
    board_features[2] = x2;
    board_features[3] = x3;
    board_features[4] = x4;
    board_features[5] = x5;
    board_features[6] = x6;
}

// Function to evaluate and assign a value to a given board state
float evaluateBoard(int features[NO_FEATURES], float weights[NO_FEATURES]) {
    float board_value = 0;
    for (int i = 0; i < NO_FEATURES; i++) {
        board_value += features[i] * weights[i];
    }
    return board_value;
}

// Function to reset the array of possible moves for the ML model to take
void resetPossibleMoves(int moves[BOARDSIZE][BOARDSIZE + 1]) {
    for (int i = 0; i < BOARDSIZE; i++) {
        for (int j = 0; j < BOARDSIZE + 1; j++) {
            if (j == 9) {
                // Set move index to -1
                moves[i][9] = -1;
            }
            else {
                // Reset
                moves[i][j] = 0;
            }
        }
    }
}

// Function for program to return a random move (One Player Mode: Easy)
int randomInput(int gameState[BOARDSIZE], int playerNo) {
    // Initialise random number generator's seed
    srand(time(NULL));
    int random_move = 0;
    do {
        // Get a random number between 0 to 8 to select a random cell on the board
        random_move = rand() % 9;
    } while (gameState[random_move] != 0); // Keep looping until an empty cell is found
    // Return the move
    return random_move;
}

// Function for ML model to evaluate the best possible move (One Player Mode: Medium)
int modelInput(float weights[NO_FEATURES], int playerNo) {
    // Initialise counter and tracking variables
    int move_index = 0, best_move = 0;
    float current_score = -999, best_score = -999;
    // Reset array of possible moves for the ML model to take
    resetPossibleMoves(possible_moves);
    // Populate 2D array containing all possible moves
    for (int i = 0; i < BOARDSIZE; i++) {
        // Check for empty cells
        if (board[i] == 0) {
            // Make a copy of the current board's state
            for (int j = 0; j < BOARDSIZE; j++) {
                possible_moves[move_index][j] = board[j];
            }
            // Set new move
            possible_moves[move_index][i] = playerNo;
            // Save index of the new move
            possible_moves[move_index][9] = i;
            // Increment move index
            move_index++;
        }
    }
    // Iterate through each possible move
    for (int i = 0; i < BOARDSIZE; i++) {
        // Check if there are any valid possible moves
        if (possible_moves[i][9] != -1) {
            // Get feature values for the current move
            getBoardFeatures(possible_moves[i], playerNo);
            // Get the score for the current move
            current_score = evaluateBoard(board_features, model_weights);
            // Evaluate move
            if (best_score < current_score) {
                best_score = current_score;
                best_move = possible_moves[i][9];
            }
        }
        else {
            // Break out of the loop if there are no more possible moves
            break;
        }
    }
    // Return the best move
    return best_move;
}         

// Function to write the ML model's weights to the settings file   
void writeWeights() {
    // Initialise file pointer for writing
    FILE *settings_file = fopen(SETTINGS_FILE, "w");
    // Check if file pointer is valid
    if (settings_file == NULL){
        printf("%s does not exist!\n", SETTINGS_FILE);
        exit(1);
    }
    // Write ML model's weights to the file
    for (int i = 0; i < NO_FEATURES; i++){
        fprintf(settings_file, "w%d = %f\n", i, model_weights[i]);
    }
    // Close file pointer
    fclose(settings_file);
}   

// Function to update the weights for the ML model features
void updateWeights(float learningConstant, int features[NO_FEATURES], float weights[NO_FEATURES], float target_actual, float target_estimated) {
    for (int i = 0; i < NO_FEATURES; i++) {
        // Update each weight to obtain lower mean squared error
	    weights[i] = weights[i] + learningConstant * (target_actual - target_estimated) * features[i];
    }
    // Update settings file
    writeWeights();
}