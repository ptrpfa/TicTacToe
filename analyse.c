#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

// Program entrypoint
int main() {

    // Dataset pre-processing
    initialiseDataset();
    stratifyDataset();

    return 0;

}

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
        // Board configurations for a win
        int board_wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};   
        // Iterate through dataset to further categorise outcomes into draws and losses
        for (int i = 0; i < DATASET_SIZE; i++){
            for (int j = 0; j < 8; j++){
                if (dataset[i][board_wins[j][0]] != 0 && dataset[i][board_wins[j][0]] == dataset[i][board_wins[j][1]] && dataset[i][board_wins[j][0]] == dataset[i][board_wins[j][2]]){ 
                    dataset[i][9] = dataset[i][board_wins[j][2]];           // Set to 1 if X won, -1 if X lost
                    break;                                                  // Break out of loop once a win is detected
                }
                else{
                    dataset[i][9] = 0;  // Set to 0 if outcome is a draw
                }
            }
        }
        // Populate array containing only wins, draws and losses
        int win_index = 0, draw_index = 0, lose_index = 0;
        for (int i = 0; i < DATASET_SIZE; i++){
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

        // TEMPORARY PRINT
        // for (int i = 0; i < 700; i++){
        //     printf("\nLine %d:\n", i + 1);
        //     printf(" %d | %d | %d\n",dataset[i][0],dataset[i][1],dataset[i][2]);
        //     printf("---+---+---\n");
        //     printf(" %d | %d | %d\n",dataset[i][3],dataset[i][4],dataset[i][5]);
        //     printf("---+---+---\n");
        //     printf(" %d | %d | %d\n",dataset[i][6],dataset[i][7],dataset[i][8]);
        //     printf("Outcome: %d", dataset[i][9]);
        // }
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