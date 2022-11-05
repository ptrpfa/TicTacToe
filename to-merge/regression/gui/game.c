#include <stdio.h>                  // Include standard functions for I/O
#include <stdlib.h>                 // Include standard library
#include <string.h>                 // Include string functions
#include <time.h>                   // Include time functions
#include <gtk/gtk.h>                // Include GTK library for GUI
#include "config.h"                 // Include configuration file
#include "miniaudio.h"              // Include Mini Audio library for playing audio

// Initialise global variables for Mini Audio library
ma_result miniaudio_result;
ma_engine miniaudio_engine;

// Program entrypoint
int main (int argc, char**argv) {
    // Read in ML weights
    readWeights();
    // Initialise Mini Audio engine
    miniaudio_result = ma_engine_init(NULL, &miniaudio_engine);
    // Check if the MA engine has been initialised successfully
    if (miniaudio_result != MA_SUCCESS) {
        printf("Failed to initialize Mini Audio Engine!");
        exit(1);
    }
    // Create a GTKApplication object
    GtkApplication* app; //app is the GTKApplication 
    int status;

    app = gtk_application_new(NULL, G_APPLICATION_DEFAULT_FLAGS); //Init App, Parameter: application name, flags for special needs 
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);//Connect App with the 'activate' function, or the settings for the GUI
    status = g_application_run(G_APPLICATION(app), argc, argv); //Accpets command line argument with argc and argv
    g_object_unref(app); //Remove it from memory
    //End of Creation

    // Close Mini Audio engine
    ma_engine_uninit(&miniaudio_engine);

    return status;
}

// Function to initialise GTK elements
static void activate(GtkApplication* app, gpointer user_data){

    /*Window Creation*/
    window = gtk_application_window_new(app);
    gtk_window_set_title( GTK_WINDOW(window), "Tic Tac Toe"); //Set Window Title
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 750); 
    /*End Window Creation*/

    //CSS
    CreateCSS(window, NULL);

    Designer();
    gtk_widget_show(window);
}

// Function to set the CSS styling for the GUI
void CreateCSS(GtkWidget *widget, const char *class_name){
    GtkCssProvider *provider2;
    GtkStyleContext *context2;

    //Init CSS
    context2 = gtk_widget_get_style_context(widget);
    provider2 = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider2, STYLES_FILE);
    gtk_style_context_add_provider(context2, GTK_STYLE_PROVIDER(provider2), GTK_STYLE_PROVIDER_PRIORITY_USER);

    //Create Class
    if(class_name != NULL){
        gtk_style_context_add_class(context2, class_name);
    }

}

// Design Controller for GUI
void Designer(){
    GtkWidget *box;

    /*Start of box design to hold all widgets*/
    //Create a contianer box which contains tic tac toe grid
    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0); 
    gtk_window_set_child (GTK_WINDOW (window), box); //Adds the box to the GUI

    //Create  header label
    headerlabel = gtk_label_new("\nWelcome to Tic Tac Toe!\n");

    //Init Label CSS
    CreateCSS(headerlabel, "headerlabel");

    //Add Label to box
    gtk_box_append(GTK_BOX(box), GTK_LABEL(headerlabel));
    gtk_widget_set_halign (headerlabel, GTK_ALIGN_CENTER); //Horizontal alignment
    gtk_widget_set_valign (headerlabel, GTK_ALIGN_CENTER); //Vertical alignment
    
    //Create the playing field
    BoardDesign();   
    //Create the Settings field
    SettingDesign();
    
    //Add all widget to the box
    gtk_box_append(GTK_BOX(box), GTK_GRID(settingGrid));
    gtk_box_append (GTK_BOX (box), GTK_GRID(boardGrid));
}

// Create the design of the settings bar
void SettingDesign(){
    GtkWidget *QuitBtn;
    //Init the settingGrid
    settingGrid = gtk_grid_new();
    //Set alignment
    gtk_grid_set_column_homogeneous(GTK_GRID(settingGrid),TRUE); 
    gtk_grid_set_row_homogeneous(GTK_GRID(settingGrid),TRUE); 
    gtk_widget_set_halign (settingGrid, GTK_ALIGN_CENTER); 
    gtk_widget_set_valign (settingGrid, GTK_ALIGN_CENTER);
    gtk_grid_set_column_spacing(GTK_GRID (settingGrid), 50); //Set each widget spacing

    //StartRestart Button in the grid (to restart the game) or (to start the game)
    StartBtn = gtk_button_new_with_label ("START"); //Set button name
    g_signal_connect(StartBtn, "clicked", G_CALLBACK(Start), NULL); //prints to command line when clicked
    // gtk_widget_set_sensitive(GTK_BUTTON(StartBtn), 0); //Set Unclickable
    gtk_widget_set_tooltip_markup(StartBtn, "This is <b>bold</b> &amp; this is <i>italics</i>");
    GdkCursor* nope = gdk_cursor_new_from_name("not-allowed", NULL);
    gtk_widget_set_cursor(StartBtn, nope);
    gtk_grid_attach (GTK_GRID (settingGrid), StartBtn, 1, 0, 1, 1);

    //Init the gameMode Dropdown box
    const char *mode[] = { "\nPLEASE ENTER A GAME MODE\n", 
                        "\nMULTIPLAYER\n", 
                        "\nPLAYER VS COMPUTER(HARD)\n", 
                        "\nPLAYER VS COMPUTER(MEDIUM)\n",
                        NULL };
    gameModeMenu = gtk_drop_down_new_from_strings(mode);
    g_signal_connect(gameModeMenu, "notify::selected", G_CALLBACK (modeController), NULL);
    gtk_grid_attach (GTK_GRID (settingGrid), gameModeMenu, 2,  0, 3, 1);
    //END of gameMode Dropdown Box

    //Create the Quit Button (to quit the game)
    QuitBtn = gtk_button_new_with_label ("QUIT"); //Set button name
    g_signal_connect_swapped (QuitBtn, "clicked", G_CALLBACK (gtk_window_destroy), window); 
    GdkCursor* quit_point = gdk_cursor_new_from_name("pointer", NULL);
    gtk_widget_set_cursor(QuitBtn, quit_point);
    gtk_grid_attach (GTK_GRID (settingGrid), QuitBtn, 6,  0, 1, 1);

    //Create CSS for StartBtn and QuitBtn and SettingGrid
    CreateCSS(settingGrid, "setting_grid");
    CreateCSS(StartBtn, "start_btn");
    CreateCSS(QuitBtn, "quit_btn");
}

// Function for controlling the game mode selection
static void modeController(GtkDropDown  *dropdown, gpointer *data){

    guint id = gtk_drop_down_get_selected (dropdown);
    if(gameModeOption == -1){ //Game just started 
        if(id != 0){
            //If one of the gameMode is selected
            //Set StartBtn to clickable
            // gtk_widget_set_sensitive(GTK_BUTTON(StartBtn), 1);
            //Reset StartBtn Cursor Pointer
            GdkCursor* point = gdk_cursor_new_from_name("pointer", NULL);
            gtk_widget_set_cursor(StartBtn, point);
            //Set Global gamemode option to selected
            gameModeOption = id;
        }
    }else{ //User re choose the game mode
        if(id != 0){
            //If one of the gameMode is selected
            //Set Global gamemode option to selected
            gameModeOption = id;
            //Change the headerLabel
            gtk_label_set_text(GTK_LABEL(headerlabel), gamemodeLabel[id]);
            //Change the Start button to start
            gtk_button_set_label(GTK_BUTTON(StartBtn), "RESTART");
            //Refresh the board
            Restart();
        }
    }

}

// Start function
static void Start(GtkWidget *widget, gpointer *data){
    //Get the Current Text of the button
    const char *btnText = gtk_button_get_label(GTK_BUTTON(widget));
    GtkWidget* buttonChild;
    if(gameModeOption != -1 && gameModeOption != 0){
        if(strcmp(btnText,"START") == 0){
            //If btn is Start
            //Set the header  Label to selected game mode
            gtk_label_set_text(GTK_LABEL(headerlabel), gamemodeLabel[gameModeOption]);
            //Set button to Restart
            gtk_button_set_label(GTK_BUTTON(widget), "RESTART");
            
            //Set the board to be playable
            Restart();
        }else if(strcmp(btnText,"RESTART") == 0){
            //Refresh the board
            Restart();
            //Set the HeaderLabel
            gtk_label_set_text(GTK_LABEL(headerlabel), gamemodeLabel[gameModeOption]);
        }
    }
}

// Restart function
void Restart(){
    GtkWidget* buttonChild;
    for(int i=0;i<9;i++){
        buttonChild = gtk_grid_get_child_at(GTK_GRID(boardGrid), ButtonPos[i][0], ButtonPos[i][1]);
        //Reset the button text
        gtk_button_set_label(GTK_BUTTON(buttonChild), " ");
        CreateCSS(GTK_BUTTON(buttonChild),"xo");
        //Reset the board var 
        board[i]=0; 
        //Allow Clicking         
        gtk_widget_set_sensitive(buttonChild, 1);
    }
    //Set back to player 1 start first
    player = -1;
}

// Create the Design for the Tic Tac Toe Board
void BoardDesign(){
    /* Here we construct the grid that is going pack our buttons */ 
    GtkWidget* button;
    boardGrid = gtk_grid_new (); 
    gtk_grid_set_column_homogeneous(GTK_GRID(boardGrid),TRUE); 
    gtk_grid_set_row_homogeneous(GTK_GRID(boardGrid),TRUE); 
    gtk_widget_set_halign (boardGrid, GTK_ALIGN_CENTER); //Horizontal alignment
    gtk_widget_set_valign (boardGrid, GTK_ALIGN_CENTER); //Vertical alignment
    
    // Init the board
    for(int i=0; i < 9; i++){ 
        GtkWidget* button;
        button = gtk_button_new_with_label(" "); //Set button name
        g_signal_connect(button, "clicked", G_CALLBACK (MainGameController), GINT_TO_POINTER(i));// (gpointer)i gives the current position of the button
        gtk_widget_set_tooltip_text(GTK_WIDGET(button), "Please select Game Mode!");
        gtk_widget_set_sensitive(button, 0);
        //Create CSS for the button
        switch(i){
            case 0:
            case 3:
                CreateCSS(button, "button1");
                break;
            case 1:
            case 2:
            case 4:
            case 5:
                CreateCSS(button, "button2");
                break;
            case 6:
                CreateCSS(button, "button3");
                break;
            case 7:
            case 8:
                CreateCSS(button, "button4");
                break;
        }
        gtk_grid_attach (GTK_GRID (boardGrid), button, ButtonPos[i][0], ButtonPos[i][1], 160, 160);
    }

}   

// Function to get the current board's status (win/lose/draw/in progress)
int checkWin() {
    // Default board status is 2 (draw) [2: Draw, -1: Player 1 won, 1: Player 2 won, 0: In progress]
    int board_status = 2;
    // Loop through each legal win configuration
    for(int i = 0; i < 8; ++i) {
        // Check if the first element is blank, and whether all positions of the board configuration matches the current board state
        if (board[board_wins[i][0]] != 0 && board[board_wins[i][0]] == board[board_wins[i][1]] && board[board_wins[i][0]] == board[board_wins[i][2]]){ 
            board_status = board[board_wins[i][2]];     // Set board status to winning player ('-1' or '1')
            return board_status;                        // Return board status immediately once a win is found
        }
    }
    // Check for any blank cells (game is still in progress)
    for (int i = 0; i < BOARDSIZE; i++){
        if(board[i] == 0){
            board_status = 0;
            return board_status; // indicate that game is still in progress
        }
    }
    // Return default board status if no wins are found (draw)
    return board_status;
}

// Function to display the game results (2 Player Mode)
int DisplayWin(int result){

    GtkWidget* buttonChild;
    switch(result){
        case 2:
            gtk_label_set_text(GTK_LABEL(headerlabel), "\nIT'S A DRAW!\n");
            audio(DRAW_SOUND);
            break;
        case -1:
            gtk_label_set_text(GTK_LABEL(headerlabel), "\nPLAYER 1 WINS!\n");
            //Make board unclickable till restart button is clicked
            for(int i=0; i < 9;i++){
                buttonChild = gtk_grid_get_child_at(GTK_GRID(boardGrid), ButtonPos[i][0], ButtonPos[i][1]);
                gtk_widget_set_sensitive(buttonChild, 0);
            }
            audio(WIN_SOUND);
            break;
        case 1:
            gtk_label_set_text(GTK_LABEL(headerlabel), "\nPLAYER 2 WINS!\n");
            for(int i=0; i < 9;i++){
                buttonChild = gtk_grid_get_child_at(GTK_GRID(boardGrid), ButtonPos[i][0], ButtonPos[i][1]);
                gtk_widget_set_sensitive(buttonChild, 0);
            }
            audio(WIN_SOUND);
            break;
    }

}

// Function to display the game results (1 Player Mode)
int DisplayWin2(int result){

    GtkWidget* buttonChild;
    switch(result){
        case 2:
            gtk_label_set_text(GTK_LABEL(headerlabel), "\nIT'S A DRAW\n");
            audio(DRAW_SOUND);
            break;
        case -1:
            gtk_label_set_text(GTK_LABEL(headerlabel), "\nPLAYER 1 WINS!\n");
            //Make board unclickable till restart button is clicked
            for(int i=0; i < 9;i++){
                buttonChild = gtk_grid_get_child_at(GTK_GRID(boardGrid), ButtonPos[i][0], ButtonPos[i][1]);
                gtk_widget_set_sensitive(buttonChild, 0);
            }
            audio(WIN_SOUND);
            break;
        case 1:
            gtk_label_set_text(GTK_LABEL(headerlabel), "\n YOU LOST!\n");
            for(int i=0; i < 9;i++){
                buttonChild = gtk_grid_get_child_at(GTK_GRID(boardGrid), ButtonPos[i][0], ButtonPos[i][1]);
                gtk_widget_set_sensitive(buttonChild, 0);
            }
            audio(LOSE_SOUND);
            break;
    }

}

// Function for checking the player number of a given game piece
int checkPlayerData(char n){
    if('X' == n){
        return -1; //Player 1
    }else if('O' == n){
        return 1; //Player 2
    }else{
        return 0; //Empty
    }
}

// Main game controller function
static void MainGameController(GtkButton *button, gpointer data){    

    int result = 0;
    switch(gameModeOption){
        case 1: // 2 Player Mode
            twoplayer(button, GPOINTER_TO_INT(data));
            result = checkWin();
            if(result !=0){ //Someone win or draw
                DisplayWin(result);
            } 
            break;
        case 2: // MiniMax
            // Get First Player's input first
            //Change the button label
            gtk_button_set_label(GTK_WIDGET(button), "X");
            CreateCSS(GTK_WIDGET(button),"xo");
            // Play sound effect for Player 1
            audio(P1_SOUND);
            // Update the global board;
            int pos = GPOINTER_TO_INT(data);
            board[pos] = -1;
            // Set the button to be non clickable after the player's move
            gtk_widget_set_sensitive(GTK_WIDGET(button), 0);
            //End of first player

            //Check Win
            result = checkWin();
            if(result == 0){ //No one win
                //AI Player Move
                int move = computerMove();
                delay(TIME_DELAY); // Wait for a set period of time before making the move
                board[move] = 1;            // AI played the best move 
                GtkWidget *buttonChild = gtk_grid_get_child_at(GTK_GRID(boardGrid), ButtonPos[move][0], ButtonPos[move][1]);
                //Set the button text
                gtk_button_set_label(GTK_BUTTON(buttonChild), "O");
                CreateCSS(GTK_BUTTON(buttonChild),"xo");
                audio(AI_SOUND2);
                gtk_widget_set_sensitive(buttonChild, 0);

                //Check if computer wins
                result = checkWin();
                if(result != 0){
                    DisplayWin2(result);
                }
            }else{
                DisplayWin2(result);
            }
            break;
        case 3: // ML Model input
            // Get First Player's input first
            //Change the button label
            gtk_button_set_label(GTK_WIDGET(button), "X");
            CreateCSS(GTK_WIDGET(button),"xo");
            // Play sound effect for Player 1
            audio(P1_SOUND);
            // Update the global board;
            int move_index = GPOINTER_TO_INT(data);
            board[move_index] = -1;
            // Set the button to be non clickable after the player's move
            gtk_widget_set_sensitive(GTK_WIDGET(button), 0);
            //End of first player

            //Check Win
            result = checkWin();
            if(result == 0){ //No one win
                //AI Player Move
                int move = modelInput(model_weights, 1);
                delay(TIME_DELAY); // Wait for a set period of time before making the move
                board[move] = 1;            // AI played the best move 
                GtkWidget *buttonChild = gtk_grid_get_child_at(GTK_GRID(boardGrid), ButtonPos[move][0], ButtonPos[move][1]);
                //Set the button text
                gtk_button_set_label(GTK_BUTTON(buttonChild), "O");
                CreateCSS(GTK_BUTTON(buttonChild),"xo");
                audio(AI_SOUND);
                gtk_widget_set_sensitive(buttonChild, 0);

                //Check if computer wins
                result = checkWin();
                if(result != 0){
                    DisplayWin2(result);
                }
            }else{
                DisplayWin2(result);
            }
            break;
        case 4: // dumb ai
            printf("code for dumb ai");
            break;
    }
}

// Function to get the users' inputs for 2 Player Mode
void twoplayer(GtkButton *button, int data){
    // Set the correct Label for the player on press button
    if(player == -1){ // First Player
        // Play sound effect for first player
        audio(P1_SOUND);
        // Change the button label
        gtk_button_set_label(GTK_WIDGET(button), "X");
        CreateCSS(GTK_WIDGET(button),"xo");
        // Update the global board;
        int pos = data;
        board[pos] = -1;
        // Set the button to be non clickable after the move
        gtk_widget_set_sensitive(GTK_WIDGET(button), 0); 
        player = 1; // Change to the next player (Player 2)
    }
    else if(player = 1){ // Second Player
        // Play sound effect for the second player
        audio(P2_SOUND);
        // Change the button label
        gtk_button_set_label(GTK_WIDGET(button), "O");
        CreateCSS(GTK_WIDGET(button),"xo");
        // Update the global board
        int pos = data;
        board[pos] = 1;
        // Set the button to be non clickable after the move
        gtk_widget_set_sensitive(GTK_WIDGET(button), 0); 
        player = -1; // Change to the next player (Player 1)
    }
}

// Function to get the MiniMax computer input
int computerMove(){
    int move = -1;          
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {        // for all moves
        if(board[i] == 0) {         // if its unoccupied
            board[i] = 1;           // try the move 
            int tempScore = -minimax(-1);    // calculate the score for the move
            board[i] = 0;           // reset the move 
            if(tempScore > score) {     // check if its greater than prev move 
                score = tempScore;          // maximising the score 
                move = i;                   // replace old i with new updated i if true
            }
        }
    }
    //returns a score based on minimax tree at a given node.
    return move;
}

// MiniMax algorithm
int minimax(int player) { //P vs Minimax
    //How is the position like for player (their turn) on board?
    int winner = checkWin();        // getting the output from checkwinner func, '0' for no winner 
    if(winner != 0)                 // checking if theres winner 
        return winner*player;                 // return if theres winner 
    
    int move = -1;
    int score = -2;     //Losing moves are preferred to no move
    int i;
    for(i = 0; i < 9; ++i) {            //For all moves,
        if(board[i] == 0) {         //If unoccupied
            board[i] = player;          //Try the move
            int thisScore = -minimax(player*-1);   //calculate the score for the move
            if(thisScore > score) {       // check if score is lesser than prev
                score = thisScore;      // minimising the score 
                move = i;            // replace old i with new updated i if true
            }               
            board[i] = 0;           //Reset move after trying
        }
    }

    if(move == -1) 
        return 0;
    
    return score;
}

// Function to play an audio sound effect
void audio(const char *audio_file){
    // Play audio  file
    ma_engine_play_sound(&miniaudio_engine, audio_file, NULL);
}

// Function to delay for a specified amount of seconds
void delay(float seconds){
    // Calculate number of clock cycles to wait for
    clock_t wait = CLOCKS_PER_SEC * seconds;
    // Get total number of clock cycles at the start
    clock_t start = clock();
    // Wait until the stipulated time has passed
    while(clock() < start + wait);
}





// ML Model Functions
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
int modelInput(float weights[NO_FEATURES], int playerNo) {
    // Initialise counter and tracking variables
    int move_index = 0, best_move = 0;
    float current_score = -999, best_score = -999;
    // Reset array of possible moves for the ML model to take
    resetPossibleMoves(possible_moves);
    // Populate 2D array containing all possible moves
    for (int i = 0; i < BOARDSIZE; i++) {
        // Check for empty cells
        if (board[i] == 0) {
            // Make a copy of the current board's state
            for (int j = 0; j < BOARDSIZE; j++) {
                possible_moves[move_index][j] = board[j];
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
    // Return the best move
    return best_move;
}         