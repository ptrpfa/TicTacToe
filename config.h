/* Configuration file for Tic Tac Toe program */
// Macros
#define DATASET "Dataset/tic-tac-toe.data"
#define BOARDSIZE 9
#define DATASET_SIZE 958        // Dataset size
#define DATASET_WINS 626        // Total number of wins in the dataset
#define DATASET_LOSSES 316      // Total number of losses in the dataset
#define DATASET_DRAWS 16        // Total number of draws in the dataset
#define TRAINING_SIZE 766       // ~80% of dataset used to training model
#define TRAINING_WINS 500      
#define TRAINING_LOSSES 253
#define TRAINING_DRAWS 13
#define TEST_SIZE 192           // ~20% of dataset used for testing model
#define TEST_WINS 126
#define TEST_LOSSES 63
#define TEST_DRAWS 3


// Global variables
int dataset[DATASET_SIZE][BOARDSIZE + 1];               // Array containing full dataset
int dataset_wins[DATASET_WINS][BOARDSIZE + 1];          // Array containing only wins within the dataset
int dataset_losses[DATASET_LOSSES][BOARDSIZE + 1];      // Array containing only losses within the dataset
int dataset_draws[DATASET_DRAWS][BOARDSIZE + 1];        // Array containing only draws within the dataset
int training_dataset[TRAINING_SIZE][BOARDSIZE + 1];     // Training dataset
int test_dataset[TEST_SIZE][BOARDSIZE + 1];             // Testing dataset

int board_state[BOARDSIZE];                                                                 // Array containing the current board state
int board_wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};   // Array containing the legal board configurations that qualify as a win

// Function prototypes
void initialiseDataset();       // Function to initialise dataset (read dataset file and populate dataset array)
void stratifyDataset();         // Function to split dataset into training and testing sets (80:20), whilst preserving the distribution of total wins/losses/draws

void printBoard(int gameState[BOARDSIZE]);          // Function to print current board state
int getBoardStatus(int gameState[BOARDSIZE]);       // Function to get the current board's status (win/lose/draw)
void playerInput(int playerNo);                     // Function to get player's input
