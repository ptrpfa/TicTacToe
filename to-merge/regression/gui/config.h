/* Configuration file for Tic Tac Toe program */

/* Macro Definitions */
// Miscellaneous Macros
#define MINIAUDIO_IMPLEMENTATION                // Mini Audio library macro

// Game Macros
#define BOARDSIZE 9                             // Board size
#define TIME_DELAY 0.05                         // Number of seconds to delay before computer makes its move
#define WIN_SOUND "files/sound/win.wav"         // Audio to be played when player wins
#define DRAW_SOUND "files/sound/draw.wav"       // Audio to be played when player gets a draw
#define LOSE_SOUND "files/sound/lose.wav"       // Audio to be played when player loses
#define P1_SOUND "files/sound/biu.wav"          // Audio to be played whenever the first player places a piece
#define P2_SOUND "files/sound/crunk.wav"        // Audio to be played whenever the second player places a piece
#define AI_SOUND "files/sound/computer1.wav"    // Audio to be played whenever the computer player places a piece
#define AI_SOUND2 "files/sound/computer2.wav"   // Audio to be played whenever the computer player places a piece
#define AI_SOUND3 "files/sound/computer3.wav"   // Audio to be played whenever the computer player places a piece
#define STYLES_FILE "files/styles.css"          // File containing the CSS styles for the GUI

// Machine Learning Macros
#define SETTINGS_FILE "files/weights.txt"       // File containing the ML model's weights
#define NO_FEATURES 7                           // Number of features

/* Global Variables */
// Game Variables
int gameModeOption = -1;                                                                                                                                // Variable to track the current game mode (-1: Game in progress)
static int player = -1;                                                                                                                                 // Variable to track the current player (-1: Player 1, 1: Player 2)
int board[9] = {0,0,0,0,0,0,0,0,0};                                                                                                                     // Global board state
int board_wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};                                                               // Array containing the legal board configurations that qualify as a win

// GTK GUI Variables
const char *gamemodeLabel[] = { "\nPLEASE SELECT A GAME MODE\n", "\n TWO PLAYER MODE\n", "\nONE PLAYER MODE (EASY)\n", "\nONE PLAYER MODE (MEDIUM)\n", "\nONE PLAYER MODE (HARD)\n"};   // Game mode options
int ButtonPos[9][2] = {{0,0},{160,0},{320,0}, {0,160},{160,160},{320,160}, {0,320},{160,320},{320,320}};                                                // Tic Tac Toe button positions
GtkWidget *window, *headerlabel, *boardGrid, *settingGrid, *StartBtn, *gameModeMenu;                                                                    // GTK elements

// Machine Learning Variables
int board_features[NO_FEATURES];                                                                                                                        // Array containing the feature values for the current board state
float model_weights[NO_FEATURES] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};                                                                                 // Array containing weights for each feature
int possible_moves[BOARDSIZE][BOARDSIZE + 1];                                                                                                           // 2D array containing possible moves for model to choose from (last element of each inner array represents the move)                                        

/* Function Prototypes */
// Game Functions
void BoardDesign();                                                                     // Function to create the Tic Tac Toe board design
static void MainGameController(GtkButton *button, gpointer data);                       // Main game controller function
int checkPlayerData(char n);                                                            // Function for checking the player number of a given game piece
int checkWin();                                                                         // Function to get the current board's status (win/lose/draw/in progress)
void twoplayer(GtkButton *button, int data);                                            // Function to get inputs for 2 Player Mode
int computerMove();                                                                     // Function to get the MiniMax computer input
int minimax(int player);                                                                // MiniMax algorithm
int DisplayWin(int result);                                                             // Function to display the game results (2 Player Mode)
int Display2Win(int result);                                                            // Function to display the game results (1 Player Mode)
void audio();                                                                           // Function to play an audio sound effect
void delay(float seconds);                                                              // Function to delay for a specified amount of seconds

// GTK GUI Functions
static void activate(GtkApplication* app, gpointer user_data);                          // Function to initialise GTK elements
void CreateCSS(GtkWidget *widget, const char *class_name);                              // Function to set the CSS styling for the GUI
void Designer();                                                                        // Design controller for the GUI
void SettingDesign();                                                                   // Function for the design of the settings bar
static void modeController(GtkDropDown  *dropdown, gpointer *data);                     // Function for controlling the game mode selection
static void Start(GtkWidget *widget, gpointer *data);                                   // Start function
void Restart();                                                                         // Restart function

// Machine Learning Functions
void getBoardFeatures(int gameState[BOARDSIZE], int playerNo);                          // Function to get the feature values for the current board's state
float evaluateBoard(int features[NO_FEATURES], float weights[NO_FEATURES]);             // Function to evaluate and assign a value to a given board state
void resetPossibleMoves(int moves[BOARDSIZE][BOARDSIZE + 1]);                           // Function to reset the array of possible moves for the ML model to take
int modelInput(float weights[NO_FEATURES], int playerNo);                               // Function for ML model to evaluate the best possible move
int randomInput(int gameState[BOARDSIZE], int playerNo);                                // Function to generate a random move
void readWeights();                                                                     // Function to read the ML model's weights from the settings file                                                                                                       