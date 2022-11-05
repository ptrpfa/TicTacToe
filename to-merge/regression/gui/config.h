/* Configuration file for Tic Tac Toe program */
// Macros
/* Game Macros */
#define BOARDSIZE 9                             // Board size

/* Machine Learning Macros */
#define SETTINGS_FILE "files/weights.txt"             // File containing the ML model's weights
#define NO_FEATURES 7                           // Number of features

// Global variables
int board_features[NO_FEATURES];                                                                // Array containing the feature values for the current board state
float model_weights[NO_FEATURES] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};                         // Array containing weights for each feature
int possible_moves[BOARDSIZE][BOARDSIZE + 1];                                                   // 2D array containing possible moves for model to choose from (last element of each inner array represents the move)                                        
int board_state[BOARDSIZE];                                                                     // Array containing the current board state
int board_wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};       // Array containing the legal board configurations that qualify as a win

// Function prototypes
/* Machine Learning Functions */
void getBoardFeatures(int gameState[BOARDSIZE], int playerNo);                                                                                      // Function to get the feature values for the current board's state
float evaluateBoard(int features[NO_FEATURES], float weights[NO_FEATURES]);                                                                         // Function to evaluate and assign a value to a given board state
void resetPossibleMoves(int moves[BOARDSIZE][BOARDSIZE + 1]);                                                                                       // Function to reset the array of possible moves for the ML model to take
void modelInput(int gameState[BOARDSIZE], float weights[NO_FEATURES], int playerNo);                                                                // Function for ML model to evaluate the best possible move and make it
void randomInput(int gameState[BOARDSIZE], int playerNo);                                                                                           // Function to make a random move
void readWeights();                                                                                                                                 // Function to read the ML model's weights from the settings file                                                                                                       

/* Game Functions */
void printBoard(int gameState[BOARDSIZE]);          // Function to print current board state
void clearBoard(int gameState[BOARDSIZE]);          // Function to clear the board state
int getBoardStatus(int gameState[BOARDSIZE]);       // Function to get the current board's status (win/lose/draw)
void playerInput(int playerNo);                     // Function to get player's input