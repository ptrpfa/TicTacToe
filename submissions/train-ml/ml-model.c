#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "config.h"

// Program entrypoint
int main(int argc, char * argv[]) {

    // Check command line arguments
    if (argc >= 2 && (strcmp(argv[1], "train") == 0 || strcmp(argv[1], "train-all") == 0)) {
        /* Train ML Model */
        // Simulate a specified number of games (AI vs AI) to pre-train the ML model
        simulateGames(NO_SIMULATION, model_weights);
        // Dataset pre-processing
        initialiseDataset();
        stratifyDataset();
        // Train and test ML model
        trainModel(training_dataset, model_weights);
        testModel(test_dataset, model_weights, 0);
        // Evaluate performance of ML model over a specified amount of games
        if (strcmp(argv[1], "train-all") == 0) {
            evaluatePerformance(1000000);
        }
    }
    else {
        // Get pre-defined ML model weights from settings file
        readWeights();
    }
    
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
// Function to initialise dataset (read dataset file and populate dataset array)
void initialiseDataset() { 
    // Initialise file pointer
    FILE * dataset_file = fopen(DATASET_FILE, "r");
    // Check if file pointer is valid
    if (dataset_file == NULL){
        printf("%s does not exist!\n", DATASET_FILE);
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

// Function to train regression model using the training dataset
void trainModel(int train_data[TRAINING_SIZE][BOARDSIZE + 1], float weights[NO_FEATURES]) {
    /*
        --Results--
        Weights generated:
        w0 = 0.057157
        w1 = 0.323193
        w2 = 0.541074
        w3 = 0.498722
        w4 = -0.664813
        w5 = 0.377607
        w6 = 0.274246

        Mean Squared Error for Training Data: 3.185723
        Root Mean Square Error for Training Data: 1.784859
        Mean Absolute Error for Training Data: 1.376389
    */
    int computer_player = 1;
    float predicted_score = -1, actual_score = 0, sum_square_error = 0, mean_square_error = 0, root_mean_square_error = 0, sum_abs_error = 0, mean_abs_error = 0; 
    // Variables for calculating the probability of error and confusion matrix values
    // float sum_prob_error = 0, prob_error = 0;
    // int true_win = 0, false_win = 0, true_draw = 0, false_draw = 0, true_loss = 0, false_loss = 0;
    // int false_wind = 0, false_winl = 0, false_draww = 0, false_drawl = 0, false_lossw = 0, false_lossd = 0;
    // Loop through each training data
    for (int i = 0; i < TRAINING_SIZE; i++) {
        // Print training data
        printf("\nTraining Set: %d", i + 1);
        printf("\n--Initial Weights--");
        for(int j = 0; j < NO_FEATURES; j++){
            printf("\nw%d = %f", j, weights[j]);
        }
        printf("\n\nBoard State:\n");
        printBoard(train_data[i]);
        // Get current training board's features
        getBoardFeatures(train_data[i], computer_player);
        // Compute predicted score for current training board
        predicted_score = evaluateBoard(board_features, weights);
        // Get actual score for current training board
        actual_score = train_data[i][9];
        // Obtain sum of the squared error
        sum_square_error += pow(actual_score - predicted_score, 2);
        // Obtain sum of the absolute error
        sum_abs_error += fabs(predicted_score - actual_score);
        // Obtain sum of errors (for probability of error calculations)
        // sum_prob_error += (actual_score == predicted_score) ? 0 : 1;
        // Check confusion matrix values
        // switch ((int) actual_score) {
        //     case 1: // win
        //         if (actual_score == predicted_score) {
        //             true_win++;
        //         }
        //         else if (predicted_score == 0) {
        //             false_wind++;
        //         }
        //         else {
        //             false_winl++;
        //         }
        //         break;
        //     case 0: // draw
        //         if (actual_score == predicted_score) {
        //             true_draw++;
        //         }
        //         else if (predicted_score == 1) {
        //             false_draww++;
        //         }
        //         else {
        //             false_drawl++;
        //         }
        //         break;
        //     case -1: // loss
        //         if (actual_score == predicted_score) {
        //             true_loss++;
        //         }
        //         else if (predicted_score == 1) {
        //             false_lossw++;
        //         }
        //         else {
        //             false_lossd++;
        //         }
        //         break;
        // };
        // Update ML model's weights
        updateWeights(learningRate, board_features, weights, actual_score, predicted_score);
        // Print training results
        printf("Predicted Score: %f\nActual Score: %f\n", predicted_score, actual_score);
        printf("\n--Updated Weights--");
        for(int j = 0; j < NO_FEATURES; j++){
            printf("\nw%d = %f", j, weights[j]);
        }
        printf("\n");
    }
    // Calculate mean square error
    mean_square_error = sum_square_error / TRAINING_SIZE;
    // Calculate root mean square error
    root_mean_square_error = sqrt(mean_square_error);
    // Calculate mean absolute error
    mean_abs_error = sum_abs_error / TRAINING_SIZE;
    // Calculate probabilty of error
    // prob_error = sum_prob_error / TRAINING_SIZE;
    printf("\nMean Squared Error for Training Data: %f\nRoot Mean Square Error for Training Data: %f\nMean Absolute Error for Training Data: %f\n\n", mean_square_error, root_mean_square_error, mean_abs_error);
    // printf("\nMean Squared Error for Training Data: %f\nRoot Mean Square Error for Training Data: %f\nMean Absolute Error for Training Data: %f\nSum of Errors: %f\nProbability of Errors: %f\n", mean_square_error, root_mean_square_error, mean_abs_error, sum_prob_error, prob_error);
    // printf("True Wins: %d\nFalse Wins (Draw): %d\nFalse Wins (Loss): %d\n", true_win, false_wind, false_winl);
    // printf("True Draws: %d\nFalse Draws (Win): %d\nFalse Draws (Loss): %d\n", true_draw, false_draww, false_drawl);
    // printf("True Losses: %d\nFalse Losses (Win): %d\nFalse Losses (Draw): %d\n\n", true_loss, false_lossw, false_lossd);
}

// Function to test regression model against the testing dataset
void testModel(int test_data[TEST_SIZE][BOARDSIZE + 1], float weights[NO_FEATURES], int train_model) {
    /*
        --Results (ML model only trained using training dataset)--
        Weights generated from training dataset:
        w0 = 0.057157
        w1 = 0.323193
        w2 = 0.541074
        w3 = 0.498722
        w4 = -0.664813
        w5 = 0.377607
        w6 = 0.274246

        Mean Squared Error for Test Data: 1.073408
        Root Mean Square Error for Test Data: 1.036054
        Mean Absolute Error for Test Data: 0.902610

        ~~Results (ML model trained using both training and test dataset)~~
        Weights generated from training on both training and test dataset:
        w0 = 0.032795
        w1 = 0.300029
        w2 = 0.536177
        w3 = 0.472087
        w4 = -0.577758
        w5 = 0.339330
        w6 = 0.314742

        Mean Squared Error for Test Data: 0.980228
        Root Mean Square Error for Test Data: 0.990065
        Mean Absolute Error for Test Data: 0.851265
    */
    int computer_player = 1;
    float predicted_score = -1, actual_score = 0, sum_square_error = 0, mean_square_error = 0, root_mean_square_error = 0, sum_abs_error = 0, mean_abs_error = 0;
    // Variables for calculating the probability of error and confusion matrix values
    // float sum_prob_error = 0, prob_error = 0;
    // int true_win = 0, false_win = 0, true_draw = 0, false_draw = 0, true_loss = 0, false_loss = 0;
    // int false_wind = 0, false_winl = 0, false_draww = 0, false_drawl = 0, false_lossw = 0, false_lossd = 0;
    // Loop through each test data
    for (int i = 0; i < TEST_SIZE; i++) {
        // Print test data
        printf("\nTesting Set: %d", i + 1);
        printf("\n\nBoard State:\n");
        printBoard(test_data[i]);
        // Get current test board's features
        getBoardFeatures(test_data[i], computer_player);
        // Compute predicted score for current test board
        predicted_score = evaluateBoard(board_features, weights);
        // Get actual score for current test board
        actual_score = test_data[i][9];
        // Obtain sum of the squared error
        sum_square_error += pow(actual_score - predicted_score, 2);
        // Obtain sum of the absolute error
        sum_abs_error += fabs(predicted_score - actual_score);
        // Obtain sum of errors (for probability of error calculations)
        // sum_prob_error += (actual_score == predicted_score) ? 0 : 1;
        // Check confusion matrix values
        // switch ((int) actual_score) {
        //     case 1: // win
        //         if (actual_score == predicted_score) {
        //             true_win++;
        //         }
        //         else if (predicted_score == 0) {
        //             false_wind++;
        //         }
        //         else {
        //             false_winl++;
        //         }
        //         break;
        //     case 0: // draw
        //         if (actual_score == predicted_score) {
        //             true_draw++;
        //         }
        //         else if (predicted_score == 1) {
        //             false_draww++;
        //         }
        //         else {
        //             false_drawl++;
        //         }
        //         break;
        //     case -1: // loss
        //         if (actual_score == predicted_score) {
        //             true_loss++;
        //         }
        //         else if (predicted_score == 1) {
        //             false_lossw++;
        //         }
        //         else {
        //             false_lossd++;
        //         }
        //         break;
        // };
        // Check if model should be trained using the test data
        if (train_model == 1) {
            // Print initial weights
            printf("\n--Initial Weights--");
            for(int j = 0; j < NO_FEATURES; j++){
                printf("\nw%d = %f", j, weights[j]);
            }
            // Update ML model's weights
            updateWeights(learningRate, board_features, weights, actual_score, predicted_score);
            // Print updated weights
            printf("\n\n--Updated Weights--");
            for(int j = 0; j < NO_FEATURES; j++){
                printf("\nw%d = %f", j, weights[j]);
            }
            printf("\n");
        }
        // Print test results
        printf("\nPredicted Score: %f\nActual Score: %f\n", predicted_score, actual_score);
    }
    // Calculate mean square error
    mean_square_error = sum_square_error / TEST_SIZE;
    // Calculate root mean square error
    root_mean_square_error = sqrt(mean_square_error);
    // Calculate the mean absolute error
    mean_abs_error = sum_abs_error / TEST_SIZE;
    // Calculate probabilty of error
    // prob_error = sum_prob_error / TEST_SIZE;
    printf("\nMean Squared Error for Test Data: %f\nRoot Mean Square Error for Test Data: %f\nMean Absolute Error for Test Data: %f\n\n\n", mean_square_error, root_mean_square_error, mean_abs_error);
    // printf("\nMean Squared Error for Training Data: %f\nRoot Mean Square Error for Training Data: %f\nMean Absolute Error for Training Data: %f\nSum of Errors: %f\nProbability of Errors: %f\n", mean_square_error, root_mean_square_error, mean_abs_error, sum_prob_error, prob_error);
    // printf("True Wins: %d\nFalse Wins (Draw): %d\nFalse Wins (Loss): %d\n", true_win, false_wind, false_winl);
    // printf("True Draws: %d\nFalse Draws (Win): %d\nFalse Draws (Loss): %d\n", true_draw, false_draww, false_drawl);
    // printf("True Losses: %d\nFalse Losses (Win): %d\nFalse Losses (Draw): %d\n\n", true_loss, false_lossw, false_lossd);
}

// Function to simulate a specified number of games (Computer vs Computer) for the regression model to be updated
void simulateGames(int game_length, float weights[NO_FEATURES]) {
    // Initialise variables
    int board_status = 9, current_player = 0, game_result = 0;
    int base_player = 1;                            // Primary player that we are using to train the ML model
    int starting_board_features[NO_FEATURES] = {};  // Array to keep a copy of the starting board's features
    float starting_score, intermediate_score, final_score;
    // Loop through each game
    for (int game_no = 1; game_no <= game_length; game_no++) {
        // Clear board before the start of each game
        clearBoard(board_state);
        // Reset board status (1 or 2 if player won, 0 if draw, 9 if still in progress/not completed)
        board_status = 9;
        // Change order of starting player for each game
        if (game_no % 2 == 0) {
            current_player = 1;
        }
        else {
            current_player = 2;
        }
        // Print game
        printf("\nSimulated Game %d\n\n", game_no);
        printBoard(board_state);
        // Loop through entire board
        for (int i = 0; i < BOARDSIZE; i++) {
            /* Get the features and score of the current board before any moves have been made */
            getBoardFeatures(board_state, base_player);                     // Get pre-move board features for the base player
            starting_score = evaluateBoard(board_features, model_weights);  // Get pre-move board score
            // Make a copy of the current board features
            for (int j = 0; j < NO_FEATURES; j++){
                starting_board_features[j] = board_features[j];
            }

            /* Get ML model's moves */
            // Get ML model's input
            modelInput(board_state, model_weights, current_player);
            // Get current board status
            board_status = getBoardStatus(board_state);
            if (board_status != 9){
                // Break out of loop once game ends
                break;
            }
            // Switch to opposing ML model's turn
            if (current_player == 1){
                current_player = 2;
            }
            else {
                current_player = 1;
            }
            // Get opposing ML model's input
            modelInput(board_state, model_weights, current_player);
            // Get current board status
            board_status = getBoardStatus(board_state);
            if (board_status != 9){
                // Break out of loop once game ends
                break;
            }
            // Switch to next player after ML model's turn
            if (current_player == 1){
                current_player = 2;
            }
            else {
                current_player = 1;
            }

            /* Get the features and score of the intermediate board, after the ML model's moves */
            getBoardFeatures(board_state, base_player);                         // Get intermediate board features for the base player
            intermediate_score = evaluateBoard(board_features, model_weights);  // Get intermediate board score

            /* Update ML model's weights after each intermediate board */
            updateWeights(learningRate, starting_board_features, model_weights, intermediate_score, starting_score); // intermediate_score is the actual value, starting_score is the predicted value
        }
        // Set game results
        if (board_status == 0){
            printf("\nDRAW!\n");
            game_result = 0; // Draw for Player 1
        }
        else if (board_status == 1){
            printf("\nPLAYER 1 WINS!\n");
            game_result = 1; // Win for Player 1
        }
        else {
            printf("\nPLAYER 2 WINS!\n");
            game_result = -1; // Loss for Player 1
        }
        
        /* Get the features and score after the completion of each game */
        getBoardFeatures(board_state, base_player);                 // Get post-game board features for the base player
        final_score = evaluateBoard(board_features, model_weights); // Get post-game board score

        /* Update ML model's weights after the completion of each game */
        updateWeights(learningRate, starting_board_features, model_weights, game_result, final_score); // game_result is the actual value, final_score is the predicted value

        printf("\n--Updated Weights--");
        for(int k = 0; k < NO_FEATURES; k++){
            printf("\nw%d = %f", k, weights[k]);
        }
        printf("\n\n");
    }
    // Clear board after game simulations
    clearBoard(board_state);
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

// Function to update the weights for the ML model features
void updateWeights(float learningConstant, int features[NO_FEATURES], float weights[NO_FEATURES], float target_actual, float target_estimated) {
    for (int i = 0; i < NO_FEATURES; i++) {
        // Update each weight to obtain lower mean squared error
	    weights[i] = weights[i] + learningConstant * (target_actual - target_estimated) * features[i];
    }
    // Update settings file
    writeWeights();
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

// Function to simulate a specified number of games (Smart AI vs Dumb AI) to quantify the performance of the regression model
void evaluatePerformance(int game_length) {
    // Initialise variables
    int board_status = 9, current_player = 0, turn = 0, win_count = 0, draw_count = 0, loss_count = 0;
    // Loop through each game
    for (int game_no = 1; game_no <= game_length; game_no++) {
        // Clear board before the start of each game
        clearBoard(board_state);
        // Reset board status (1 or 2 if player won, 0 if draw, 9 if still in progress/not completed)
        board_status = 9;
        // Print game
        printf("\nPerformance Evaluation Game %d\n\n", game_no);
        printBoard(board_state);
        // Alternate starting player
        if (game_no % 2 == 0) {
            current_player = 1;
            turn = 0;
        }
        else {
            current_player = 2;
            turn = 1;
        }
        // Loop through entire board
        for (int i = 0; i < BOARDSIZE; i++) {
            // Smart AI to go first
            if (turn == 0) {
                // Get smart AI's input
                modelInput(board_state, model_weights, current_player);
                // Get current board status
                board_status = getBoardStatus(board_state);
                if (board_status != 9){
                    // Break out of loop once game ends
                    break;
                }
                // Switch to next player after smart AI's turn
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
                    // Break out of loop once game ends
                    break;
                }
                // Switch to next player after dumb AI's turn
                if (current_player == 1){
                    current_player = 2;
                }
                else {
                    current_player = 1;
                }
            }
            // Dumb AI to go first
            else {
                // Get dumb AI's input
                randomInput(board_state, current_player);
                // Get current board status
                board_status = getBoardStatus(board_state);
                if (board_status != 9){
                    // Break out of loop once game ends
                    break;
                }
                // Switch to next player after dumb AI's turn
                if (current_player == 1){
                    current_player = 2;
                }
                else {
                    current_player = 1;
                }
                // Get smart AI's input
                modelInput(board_state, model_weights, current_player);
                // Get current board status
                board_status = getBoardStatus(board_state);
                if (board_status != 9){
                    // Break out of loop once game ends
                    break;
                }
                // Switch to next player after smart AI's turn
                if (current_player == 1){
                    current_player = 2;
                }
                else {
                    current_player = 1;
                }
            }
        }
        // Set game results
        if (board_status == 0){
            printf("\nDRAW!\n");
            draw_count++;
        }
        else if (board_status == 1){
            printf("\nPLAYER 1 WINS!\n");
            win_count++;
        }
        else {
            printf("\nPLAYER 2 WINS!\n");
            loss_count++;
        }
    }
    // Clear board after game simulations
    clearBoard(board_state);
    // Print results
    printf("\n\nTotal games played against dumb AI: %d\nWins: %d\nDraws: %d\nLosses: %d\n", game_length, win_count, draw_count, loss_count);
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

/* Game Functions */
// Function to print current board state
void printBoard(int gameState[BOARDSIZE]) {
    printf("  %2d  |  %2d  |  %2d\n",gameState[0],gameState[1],gameState[2]);
    printf("------+------+------\n");
    printf("  %2d  |  %2d  |  %2d\n",gameState[3],gameState[4],gameState[5]);
    printf("------+------+------\n");
    printf("  %2d  |  %2d  |  %2d\n\n",gameState[6],gameState[7],gameState[8]);
}

// Function to clear the board state
void clearBoard(int gameState[BOARDSIZE]) {
    for (int i = 0; i < BOARDSIZE; i++) {
        gameState[i] = 0;
    }
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