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
    // Initialise current player and board status
    int current_player = 1; // Players: Player 1 or 2
    int board_status = 0;
    printBoard(board_state);
    // Loop through entire board size
    for (int i = 0; i < BOARDSIZE; i++){
        // Get player's input
        playerInput(current_player);
        // Get current board status
        board_status = getBoardStatus(board_state);
        if (board_status != 0){
            break;
        }
        // Change to the current player to the next player
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