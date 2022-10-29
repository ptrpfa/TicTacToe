/* Configuration file for Tic Tac Toe program */
// Macros
#define DATASET "Dataset/tic-tac-toe.data"
#define BOARDSIZE 9
#define DATASET_SIZE 958        // Dataset size
#define DATASET_WINS 626        // Total number of wins in the dataset
#define DATASET_LOSSES 316      // Total number of losses in the dataset
#define DATASET_DRAWS 16        // Total number of draws in the dataset
#define TRAINING_SIZE 766       // ~80% of dataset used to training model
#define TRAINING_WINS 500       // Total number of wins in the training dataset
#define TRAINING_LOSSES 253     // Total number of losses in the training dataset
#define TRAINING_DRAWS 13       // Total number of draws in the training dataset
#define TEST_SIZE 192           // ~20% of dataset used for testing model
#define TEST_WINS 126           // Total number of wins in the test dataset
#define TEST_LOSSES 63          // Total number of losses in the test dataset
#define TEST_DRAWS 3            // Total number of draws in the test dataset
#define NO_FEATURES 7           // Number of features

// Global variables
int dataset[DATASET_SIZE][BOARDSIZE + 1];                                                       // Array containing full dataset
int dataset_wins[DATASET_WINS][BOARDSIZE + 1];                                                  // Array containing only wins within the dataset
int dataset_losses[DATASET_LOSSES][BOARDSIZE + 1];                                              // Array containing only losses within the dataset
int dataset_draws[DATASET_DRAWS][BOARDSIZE + 1];                                                // Array containing only draws within the dataset
int training_dataset[TRAINING_SIZE][BOARDSIZE + 1];                                             // Training dataset
int test_dataset[TEST_SIZE][BOARDSIZE + 1];                                                     // Testing dataset
int board_features[NO_FEATURES];                                                                // Array containing the feature values for the current board state
float model_weights[NO_FEATURES] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};                         // Array containing weights for each feature
int possible_moves[BOARDSIZE][BOARDSIZE + 1];                                                   // 2D array containing possible moves for model to choose from (last element of each inner array represents the move)                                        
float learningRate = 0.001;                                                                     // Learning rate for ML model
int board_state[BOARDSIZE];                                                                     // Array containing the current board state
int board_wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};       // Array containing the legal board configurations that qualify as a win

// Function prototypes
/* Machine Learning Functions */
void initialiseDataset();                                                                                                                           // Function to initialise dataset (read dataset file and populate dataset array)
void stratifyDataset();                                                                                                                             // Function to split dataset into training and testing sets (80:20), whilst preserving the distribution of total wins/losses/draws
void getBoardFeatures(int gameState[BOARDSIZE], int playerNo);                                                                                      // Function to get the feature values for the current board's state
float evaluateBoard(int features[NO_FEATURES], float weights[NO_FEATURES]);                                                                         // Function to evaluate and assign a value to a given board state
void resetPossibleMoves(int moves[BOARDSIZE][BOARDSIZE + 1]);                                                                                       // Function to reset the array of possible moves for the ML model to take
void modelInput(int gameState[BOARDSIZE], float weights[NO_FEATURES], int playerNo);                                                                // Function for ML model to evaluate the best possible move and make it
void updateWeights (float learningConstant, int features[NO_FEATURES], float weights[NO_FEATURES], float target_actual, float target_estimated);    // Function to update the weights for the ML model features
void trainModel(int train_data[TRAINING_SIZE][BOARDSIZE + 1], float weights[NO_FEATURES]);                                                          // Function to train regression model using training dataset
void testModel(int test_data[TEST_SIZE][BOARDSIZE + 1], float weights[NO_FEATURES], int train_model);                                               // Function to test regression model against the test dataset
void simulateGames(int game_length, float weights[NO_FEATURES]);                                                                                    // Function to simulate a specified number of games (Computer vs Computer) for the regression model to be updated
/* Game Functions */
void printBoard(int gameState[BOARDSIZE]);          // Function to print current board state
void clearBoard(int gameState[BOARDSIZE]);          // Function to clear the board state
int getBoardStatus(int gameState[BOARDSIZE]);       // Function to get the current board's status (win/lose/draw)
void playerInput(int playerNo);                     // Function to get player's input
