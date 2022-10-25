#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

// Program entrypoint
int main() {

    // Dataset pre-processing
    initialiseDataset();
    stratifyDataset();
    
    /* Two Player Mode */
    // // Initialise current player and board status
    // int current_player = 1; // Players: Player 1 or 2
    // int board_status = 0;
    // printBoard(board_state);
    // // Loop through entire board
    // for (int i = 0; i < BOARDSIZE; i++){
    //     // Get player's input
    //     playerInput(current_player);
    //     // Get current board status
    //     board_status = getBoardStatus(board_state);
    //     if (board_status != 0){
    //         break;
    //     }
    //     // Switch to next player after current player's turn
    //     if (current_player == 1){
    //         current_player = 2;
    //     }
    //     else {
    //         current_player = 1;
    //     }
    // }

    /* Train ML Model */
    int computer_player = 1;
    float predicted_score = -1, actual_score = 0;
    for (int i = 0; i < TRAINING_SIZE; i++) {
        
        printf("\nTraining %d:", i);
        for(int j = 0; j < NO_FEATURES; j++){
            printf("\nw%d = %f", j, model_weights[j]);
        }

        // Get current training board's features
        getBoardFeatures(training_dataset[i], computer_player);
        // Compute predicted score for current training board
        predicted_score = evaluateBoard(board_features, model_weights);
        // Get actual score for current training board
        actual_score = training_dataset[i][9];
        // Update ML model's weights
        updateWeights(learningRate, board_features, model_weights, actual_score, predicted_score);

        printf("\nAfter Training %d:", i);
        for(int j = 0; j < NO_FEATURES; j++){
            printf("\nw%d = %f", j, model_weights[j]);
        }
        printf("\n");
    }

    /* One Player Mode */
    // Initialise current player and board status
    int current_player = 1; // Players: Player 1 or 2
    int board_status = 0;
    printBoard(board_state);
    // Loop through entire board
    for (int i = 0; i < BOARDSIZE; i++) {
        // Get ML model's input
        modelInput(board_state, model_weights, current_player);
        // Get current board status
        board_status = getBoardStatus(board_state);
        if (board_status != 0){
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
        if (board_status != 0){
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

    return 0;

}

/* Machine Learning Functions */
// Function to initialise dataset (read dataset file and populate dataset array)
void initialiseDataset() { 
    // Initialise file pointer
    FILE * dataset_file = fopen(DATASET, "r");
    // Check if file pointer is valid
    if (dataset_file == NULL){
        printf("%s does not exist!\n", DATASET);
        exit(1);
    }
    else {
        char current_line[27];              // String to store each line of the file (ie "o,o,x,x,x,o,o,x,x,negative", total of 26 + 1 characters)
        char position_values[BOARDSIZE];    // Array of characters to store the value of each grid position
        char outcome[9];                    // String to store the outcome of each board config (ie "positive" or "negative", total of 8 + 1 characters)
        // Read file and populate dataset array
        for (int i = 0; i < DATASET_SIZE; i++){
            // Read current line in the file
            fscanf(dataset_file, "%s", current_line);
            // Parse current line
            sscanf(current_line, "%c,%c,%c,%c,%c,%c,%c,%c,%c,%s", &position_values[0], &position_values[1], &position_values[2], &position_values[3], &position_values[4], &position_values[5], &position_values[6], &position_values[7], &position_values[8], outcome); 

            /*
                Populate dataset array[i][j], whereby [i] indicates the line number, and [j] indicates the board layout/result
                [i][0-8] indicates each cell value
                [i][9] indicates the result of each board configuration 
            */

            // Populate board configuration
            for (int j = 0; j < BOARDSIZE; j++){
                switch(position_values[j]){
                    case 'x':
                        dataset[i][j] = 1;  // 1 = X (player X, main and first player)
                        break;
                    case 'o':
                        dataset[i][j] = -1; // -1 = O (player O, opposing player)
                        break;
                    case 'b':
                        dataset[i][j] = 0;  // 0 = b (blank)
                        break;
                }
            }
            // Populate board results
            if (strcmp(outcome, "positive") == 0){
                dataset[i][BOARDSIZE] = 1;  // 1 = win
            }
            else if (strcmp(outcome, "negative") == 0){
                dataset[i][BOARDSIZE] = -1; // -1 = lose or draw
            }
        }
        // Close file pointer
        fclose(dataset_file);
        // Iterate through dataset to further categorise outcomes into draws and losses
        for (int i = 0; i < DATASET_SIZE; i++){
            dataset[i][9] = getBoardStatus(dataset[i]);
        }
        // Populate arrays containing only wins, draws and losses
        int win_index = 0, draw_index = 0, lose_index = 0;
        for (int i = 0; i < DATASET_SIZE; i++) {
            if (dataset[i][9] == 1){
                for(int j = 0; j <= BOARDSIZE; j++){
                    dataset_wins[win_index][j] = dataset[i][j];
                }
                win_index++;
            } 
            else if (dataset[i][9] == -1){
                for(int j = 0; j <= BOARDSIZE; j++){
                    dataset_losses[lose_index][j] = dataset[i][j];
                }
                lose_index++;
            }
            else{
                for(int j = 0; j <= BOARDSIZE; j++){
                    dataset_draws[draw_index][j] = dataset[i][j];
                }
                draw_index++;
            }
        }
    }
}

// Function to split dataset into training and testing sets (80:20), whilst preserving the distribution of total wins/losses/draws
void stratifyDataset() {
    int win_index = 0, draw_index = 0, lose_index = 0;
    // Populate training dataset
    for (int i = 0; i < TRAINING_SIZE; i++){
        // Populate wins
        if (i < TRAINING_WINS) {
            for (int j = 0; j <= BOARDSIZE; j++){
                training_dataset[i][j] = dataset_wins[win_index][j];
            }
            win_index++;
        }
        // Populate losses
        else if (i < TRAINING_WINS + TRAINING_LOSSES) {
            for (int j = 0; j <= BOARDSIZE; j++){
                training_dataset[i][j] = dataset_losses[lose_index][j];
            }
            lose_index++;
        }
        // Populate draws
        else {
            for (int j = 0; j <= BOARDSIZE; j++){
                training_dataset[i][j] = dataset_draws[draw_index][j];
            }
            draw_index++;
        }
    }
    // Populate test dataset
    for (int i = 0; i < TEST_SIZE; i++){
        // Populate wins
        if (i < TEST_WINS) {
            for (int j = 0; j <= BOARDSIZE; j++){
                test_dataset[i][j] = dataset_wins[win_index][j];
            }
            win_index++;
        }
        // Populate losses
        else if (i < TEST_WINS + TEST_LOSSES) {
            for (int j = 0; j <= BOARDSIZE; j++){
                test_dataset[i][j] = dataset_losses[lose_index][j];
            }
            lose_index++;
        }
        // Populate draws
        else {
            for (int j = 0; j <= BOARDSIZE; j++){
                test_dataset[i][j] = dataset_draws[draw_index][j];
            }
            draw_index++;
        }
    }
}

// Function to get the feature values for the current board's state
void getBoardFeatures(int gameState[BOARDSIZE], int playerNo) {
    /* 
        Board features (x0 to x6):
        x0: Constant value of 1
        x1: Number of rows, columns and diagonals with 2 of the selected player's pieces and 1 empty cell
        x2: Number of rows, columns and diagonals with 2 of the opposing player's pieces and 1 empty cell
        x3: Indicates if the selected player's piece is in the center cell
        x4: Number of the selected player's pieces that are in the corner cells
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
            if (row == col) {
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
            if ((row + col) == 2) {
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
                temp_value = current_board[2 - j][j];
            }
            else {
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
    board_features[6] = x6; // Consider altering for negative values (ie -1 for loss, 0 for draw, 1 for win)
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

// Function for ML model to evaluate the best possible move and make it
void modelInput(int gameState[BOARDSIZE], float weights[NO_FEATURES], int playerNo) {
    // Initialise counter and tracking variables
    int move_index = 0, best_move = 0;
    float current_score = -1, best_score = -1;
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

// Function to update the weights for the ML model features
void updateWeights(float learningConstant, int features[NO_FEATURES], float weights[NO_FEATURES], float target_actual, float target_estimated) {
    for (int i = 0; i < NO_FEATURES; i++) {
        // Update each weight
	    weights[i] = weights[i] + learningConstant * (target_actual - target_estimated) * features[i];
    }
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

// Function to get the current board's status (win/lose/draw)
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
    // Return default board status if no wins are found
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