// This program is a stripped down version of the ml-model.c program. This program only contains the essential components to utilise the trained ML model

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "config.h"

// Program entrypoint
int main(int argc, char * argv[]) {

    
    // Get pre-defined ML model weights from settings file
    readWeights();
    
    /* Tic Tac Toe Game */
    // Get user mode
    int mode = 0;
    do {
        printf("\nSelect a game mode:\n(1) Two player mode\n(2) Play against Smart AI\n(3) Play against Dumb AI\nEnter your choice: ");
        scanf("%d", &mode);
    } while (mode != 1 && mode != 2 && mode != 3);
    // Initialise current player and board status
    int current_player = 1; // Players: Player 1 or 2
    int board_status = 9;   // Board Status: 1 or 2 if player won, 0 if draw, 9 if still in progress/not completed
    srand(time(NULL));      // Initialise random number generator's seed
    int turn = rand() % 2;  // Generate random number between 0 and 1 to check whether AI or player should go first
    // Check user mode selected
    switch (mode) {
        case 1:
            /* Two Player Mode */
            printBoard(board_state);
            // Loop through entire board
            for (int i = 0; i < BOARDSIZE; i++){
                // Get player's input
                playerInput(current_player);
                // Get current board status
                board_status = getBoardStatus(board_state);
                if (board_status != 9){
                    break;
                }
                // Switch to next player after current player's turn
                if (current_player == 1){
                    current_player = 2;
                }
                else {
                    current_player = 1;
                }
            }
            // Print results
            if (board_status == 0){
                printf("\nDRAW!");
            }
            else if (board_status == 1){
                printf("\nPLAYER 1 WINS!");
            }
            else {
                printf("\nPLAYER 2 WINS!");
            }
            // Break out of case
            break;
        case 2:
            /* One Player Mode against Smart AI */
            printBoard(board_state);
            // Loop through entire board
            for (int i = 0; i < BOARDSIZE; i++) {
                // Let ML model go first if turn = 1
                if (turn){
                    // Get ML model's input
                    modelInput(board_state, model_weights, current_player);
                    // Get current board status
                    board_status = getBoardStatus(board_state);
                    if (board_status != 9){
                        break;
                    }
                    // Switch to next player after ML model's turn
                    if (current_player == 1){
                        current_player = 2;
                    }
                    else {
                        current_player = 1;
                    }

                    // Get player's input
                    playerInput(current_player);
                    // Get current board status
                    board_status = getBoardStatus(board_state);
                    if (board_status != 9){
                        break;
                    }
                    // Switch to ML model's turn
                    if (current_player == 1){
                        current_player = 2;
                    }
                    else {
                        current_player = 1;
                    }
                }
                // Let player go first if turn = 0
                else {
                    // Get player's input
                    playerInput(current_player);
                    // Get current board status
                    board_status = getBoardStatus(board_state);
                    if (board_status != 9){
                        break;
                    }
                    // Switch to ML model's turn
                    if (current_player == 1){
                        current_player = 2;
                    }
                    else {
                        current_player = 1;
                    }

                    // Get ML model's input
                    modelInput(board_state, model_weights, current_player);
                    // Get current board status
                    board_status = getBoardStatus(board_state);
                    if (board_status != 9){
                        break;
                    }
                    // Switch to next player after ML model's turn
                    if (current_player == 1){
                        current_player = 2;
                    }
                    else {
                        current_player = 1;
                    }
                }
            }
            // Print results
            if (board_status == 0){
                printf("\nDRAW!");
            }
            else if (board_status == 1){
                printf("\nPLAYER 1 WINS!");
            }
            else {
                printf("\nPLAYER 2 WINS!");
            }
            // Break out of case
            break;
        case 3:
            /* One Player Mode against Dumb AI */
            printBoard(board_state);
            // Loop through entire board
            for (int i = 0; i < BOARDSIZE; i++) {
                // Let dumb AI go first if turn = 1
                if (turn){
                    // Get dumb AI's input
                    randomInput(board_state, current_player);
                    // Get current board status
                    board_status = getBoardStatus(board_state);
                    if (board_status != 9){
                        break;
                    }
                    // Switch to next player after computer's turn
                    if (current_player == 1){
                        current_player = 2;
                    }
                    else {
                        current_player = 1;
                    }

                    // Get player's input
                    playerInput(current_player);
                    // Get current board status
                    board_status = getBoardStatus(board_state);
                    if (board_status != 9){
                        break;
                    }
                    // Switch to computer's turn
                    if (current_player == 1){
                        current_player = 2;
                    }
                    else {
                        current_player = 1;
                    }
                }
                // Let player go first if turn = 0
                else {
                    // Get player's input
                    playerInput(current_player);
                    // Get current board status
                    board_status = getBoardStatus(board_state);
                    if (board_status != 9){
                        break;
                    }
                    // Switch to computer's turn
                    if (current_player == 1){
                        current_player = 2;
                    }
                    else {
                        current_player = 1;
                    }

                    // Get dumb AI's input
                    randomInput(board_state, current_player);
                    // Get current board status
                    board_status = getBoardStatus(board_state);
                    if (board_status != 9){
                        break;
                    }
                    // Switch to next player after computer's turn
                    if (current_player == 1){
                        current_player = 2;
                    }
                    else {
                        current_player = 1;
                    }
                }
            }
            // Print results
            if (board_status == 0){
                printf("\nDRAW!");
            }
            else if (board_status == 1){
                printf("\nPLAYER 1 WINS!");
            }
            else {
                printf("\nPLAYER 2 WINS!");
            }
            // Break out of case
            break;
    }
    // End program
    return 0;
}

/* Machine Learning Functions */
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

    // Ternary classification (discretize continuous values generated by regression model)
    // if (board_value > 1){
    //     board_value = 1; // If board value is more than 1, classify as 1
    // }
    // else if (board_value < -1){
    //     board_value = -1; // If board value is less than -1, classify as -1
    // }
    // else {
    //     board_value = round(board_value); // If board value x, is between -1 < x < 1, round it off to the nearest integer
    // }

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

// Function for ML model to evaluate the best possible move and make it
void modelInput(int gameState[BOARDSIZE], float weights[NO_FEATURES], int playerNo) {
    // Initialise counter and tracking variables
    int move_index = 0, best_move = 0;
    float current_score = -999, best_score = -999;
    printf("\nPlayer %d's turn!\n", playerNo);
    // Reset array of possible moves for the ML model to take
    resetPossibleMoves(possible_moves);
    // Populate 2D array containing all possible moves
    for (int i = 0; i < BOARDSIZE; i++) {
        // Check for empty cells
        if (gameState[i] == 0) {
            // Make a copy of the current board's state
            for (int j = 0; j < BOARDSIZE; j++) {
                possible_moves[move_index][j] = gameState[j];
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
    // Set the best move
    board_state[best_move] = playerNo;
    printBoard(board_state);
}                                          

// Function for program to make a random move
void randomInput(int gameState[BOARDSIZE], int playerNo) {
    // Initialise random number generator's seed
    srand(time(NULL));
    int random_move = 0;
    do {
        // Get a random number between 0 to 8 to select a random cell on the board
        random_move = rand() % 9;
    } while (gameState[random_move] != 0); // Keep looping until an empty cell is found
    // Set the move
    gameState[random_move] = playerNo;
    printf("\nPlayer %d's turn!\n", playerNo);
    printBoard(gameState);
}

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

/* Game Functions */
// Function to print current board state
void printBoard(int gameState[BOARDSIZE]) {
    printf("  %2d  |  %2d  |  %2d\n",gameState[0],gameState[1],gameState[2]);
    printf("------+------+------\n");
    printf("  %2d  |  %2d  |  %2d\n",gameState[3],gameState[4],gameState[5]);
    printf("------+------+------\n");
    printf("  %2d  |  %2d  |  %2d\n\n",gameState[6],gameState[7],gameState[8]);
}

// Function to get the current board's status (win/lose/draw/in progress)
int getBoardStatus(int gameState[BOARDSIZE]) {
    // Default board status is 0 (draw)
    int board_status = 0;
    // Loop through each legal win configuration
    for (int i = 0; i < 8; i++) {
        if (gameState[board_wins[i][0]] != 0 && gameState[board_wins[i][0]] == gameState[board_wins[i][1]] && gameState[board_wins[i][0]] == gameState[board_wins[i][2]]) { 
            board_status = gameState[board_wins[i][2]]; // Set board status to winning player
            return board_status;                        // Return board status immediately once a win is found
        }
    }
    // Check for any blank cells (game is still in progress)
    for (int i = 0; i < BOARDSIZE; i++){
        if (gameState[i] == 0){
            board_status = 9;
            return board_status; // indicate that game is still in progress
        }
    }
    // Return default board status if no wins are found (draw)
    return board_status;
}

// Function to get player's input
void playerInput(int playerNo){
    int player_move = 0;
    printf("\nPlayer %d's turn!", playerNo);
    do {
        printf("\nSelect the position (0 to 8) to place your piece: ");
        scanf("%d", &player_move);

        // Check if move is legal
        if (player_move < 0 || player_move >= BOARDSIZE) {
            printf("\nIllegal move!");
            continue;
        }
        // Check if current cell selected is occupied
        else if (board_state[player_move] != 0) { 
            printf("\nPosition %d is already occupied!", player_move);
            continue;
        }
        // Set current move
        else {
            board_state[player_move] = playerNo;
            printBoard(board_state);
            break;
        }
    } while (1);
}