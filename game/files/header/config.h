/* Configuration file for Tic Tac Toe program */

/* Macro Definitions */
// Miscellaneous Macros
#define FILE_DIR "files/"                       // Parent directory for all files
#define SOUND_DIR FILE_DIR "sound/"             // Directory containing sound files
#define MINIAUDIO_IMPLEMENTATION                // Mini Audio library macro

// Game Macros
#define BOARDSIZE 9                             // Board size
#define TIME_DELAY 0.05                         // Number of seconds to delay before computer makes its move
#define WIN_SOUND SOUND_DIR "win.wav"           // Audio to be played when player wins
#define DRAW_SOUND SOUND_DIR "draw.wav"         // Audio to be played when player gets a draw
#define LOSE_SOUND SOUND_DIR "lose.wav"         // Audio to be played when player loses
#define P1_SOUND SOUND_DIR "biu.wav"            // Audio to be played whenever the first player places a piece
#define P2_SOUND SOUND_DIR "crunk.wav"          // Audio to be played whenever the second player places a piece
#define AI_SOUND SOUND_DIR "computer1.wav"      // Audio to be played whenever the computer player places a piece
#define AI_SOUND2 SOUND_DIR "computer2.wav"     // Audio to be played whenever the computer player places a piece
#define AI_SOUND3 SOUND_DIR "computer3.wav"     // Audio to be played whenever the computer player places a piece
#define STYLES_FILE FILE_DIR "styles.css"       // File containing the CSS styles for the GUI

// Machine Learning Macros
#define SETTINGS_FILE FILE_DIR "weights.txt"    // File containing the ML model's weights
#define NO_FEATURES 7                           // Number of features

/* Global Variables */
// Game Variables
extern int gameModeOption;                      // Variable to track the current game mode [-1: Game just started, 1: 2 Player Mode, 2: 1 Player Mode (Easy), 3: 1 Player Mode (Medium), 4: 1 Player Mode (Hard)]
extern int player;                              // Variable to track the current player (-1: Player 1, 1: Player 2)
extern int board[9];                            // Global board state
extern int board_wins[8][3];                    // Array containing the legal board configurations that qualify as a win

// GTK GUI Variables
extern const char *gamemode[];                  // Game mode options
extern GtkWidget *gameModeMenu;                 // Game mode dropdown box
extern GtkWidget *window; 
extern GtkWidget *headerLabel;
extern GtkWidget *settingGrid;
extern GtkWidget *turnLabel;  
extern GtkWidget *StartBtn;
extern GtkWidget *boardGrid;
extern int ButtonPos[9][2];                     // Tic Tac Toe button positions
extern GtkWidget *scoreGrid;

// Machine Learning Variables
extern int board_features[NO_FEATURES];                 // Array containing the feature values for the current board state
extern float model_weights[NO_FEATURES];                // Array containing weights for each feature
extern int possible_moves[BOARDSIZE][BOARDSIZE + 1];    // 2D array containing possible moves for model to choose from (last element of each inner array represents the move)                                        
extern float learningRate;                              // Learning rate for ML model

/* Function Prototypes */
// Game Functions
void MainGameController(GtkButton *button, gpointer data);                       // Main game controller function
void delay(float seconds);                                                       // Function to delay for a specified amount of seconds
int checkWin();                                                                  // Function to get the current board's status (win/lose/draw/in progress)
void DisplayWin(int result);                                                     // Function to display the game results (2 Player Mode)
void twoplayer(GtkButton *button, int data);                                     // Function to get inputs for 2 Player Mode
int computerMove();                                                              // Function to get the MiniMax computer input
int minimax(int player);                                                         // MiniMax algorithm

// GTK GUI Functions
void activate(GtkApplication* app, gpointer user_data);                          // Function to initialise GTK elements
void CreateCSS(GtkWidget *widget, const char *class_name);                       // Function to set the CSS styling for the GUI
void DesignModel();                                                              // Design controller for the GUI
void SettingDesign();                                                            // Function for the design of the settings bar
void modeController(GtkDropDown  *dropdown, gpointer *data);                     // Function for controlling the game mode selection
void Start(GtkWidget *startbtn, gpointer *data);                                 // Start function
void Restart();                                                                  // Restart function
void BoardDesign();                                                              // Function to create the Tic Tac Toe board design
void Scoreboard();                                                               // Scoreboard Feature
void SetScore();                                                                 // Set scores on Scoreboard

// Machine Learning Functions
void getBoardFeatures(int gameState[BOARDSIZE], int playerNo);                                                                                      // Function to get the feature values for the current board's state
float evaluateBoard(int features[NO_FEATURES], float weights[NO_FEATURES]);                                                                         // Function to evaluate and assign a value to a given board state
void resetPossibleMoves(int moves[BOARDSIZE][BOARDSIZE + 1]);                                                                                       // Function to reset the array of possible moves for the ML model to take
int modelInput(float weights[NO_FEATURES], int playerNo);                                                                                           // Function for ML model to evaluate the best possible move
int randomInput(int gameState[BOARDSIZE], int playerNo);                                                                                            // Function to generate a random move
void readWeights();                                                                                                                                 // Function to read the ML model's weights from the settings file                                                                                                       
void writeWeights();                                                                                                                                // Function to write the ML model's weights to the settings file   
void updateWeights(float learningConstant, int features[NO_FEATURES], float weights[NO_FEATURES], float target_actual, float target_estimated);     // Function to update the weights for the ML model features
//MiniAudio Functions
void miniaudio_init();
void miniaudio_close();
void audio(const char *audio_file);                                                     // Function to play an audio sound effect

