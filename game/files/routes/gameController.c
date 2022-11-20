#include <gtk/gtk.h>                // Include GTK library for GUI
#include "../header/config.h"       // Include configuration file

//Global Var
int board_wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};

/* Game Functions */
// Main game controller function
void MainGameController(GtkButton *button, gpointer data){
    int result = 0;
    int move_index = 0;

    // Initialise variables for ML model's continual learning
    int board_status = 0, game_result = 0, base_player = 1; // Base player is the primary player that we are using to train the ML model
    int starting_board_features_player[NO_FEATURES] = {};   // Array to keep a copy of the starting board's features before the player's move
    int starting_board_features_ai[NO_FEATURES] = {};       // Array to keep a copy of the starting board's features before the computer's move
    float starting_score_player, intermediate_score_player, final_score_player, starting_score_ai, intermediate_score_ai, final_score_ai;
    
    // Game Mode Options: -1: Game just started, 1: 2 Player Mode, 2: 1 Player Mode (Easy), 3: 1 Player Mode (Medium), 4: 1 Player Mode (Hard)
    switch(gameModeOption){
        case 1: 
            /* 2 Player Mode */
            twoplayer(button, GPOINTER_TO_INT(data));   // Get player's move
            
            // Check the board's status (win/lose/draw/in progress)
            result = checkWin();                        
            if(result !=0){
                // Display results once game has ended
                DisplayWin(result);
            } 
            // Break out of case
            break;
        case 2: /* One Player Mode: Easy (against dumb AI, random moves) */
            /* First Player's Move */
            gtk_button_set_label(button, "X");          // Change the button label
            CreateCSS(GTK_WIDGET(button),"xo");                     // Add CSS class to button
            audio(P1_SOUND);                                        // Play sound effect for Player 1
            move_index = GPOINTER_TO_INT(data);                     // Get the player's move
            board[move_index] = -1;                                 // Set the player's move on the board
            gtk_widget_set_sensitive(GTK_WIDGET(button), 0);        // Set the button to be non clickable after the player's move

            // Check the board's status (win/lose/draw/in progress)
            result = checkWin();
            if(result == 0){ // Game still in progress
                /* Dumb AI (Random)'s Move */
                int move = randomInput(board, 1);           // Get random move
                delay(TIME_DELAY);                          // Wait for a set period of time before making the move
                board[move] = 1;                            // Set random move
                GtkWidget *buttonChild = gtk_grid_get_child_at(GTK_GRID(boardGrid), ButtonPos[move][0], ButtonPos[move][1]);
                gtk_button_set_label(GTK_BUTTON(buttonChild), "O");     // Set the button text
                CreateCSS(GTK_WIDGET(buttonChild),"xo");                // Add CSS class to button
                audio(AI_SOUND3);                                       // Play sound effect for Computer Player
                gtk_widget_set_sensitive(buttonChild, 0);               // Set the button to be non clickable after the computer's move
                
                // Check the board's status (win/lose/draw/in progress)
                result = checkWin();
                if(result != 0){
                    // Display results once game has ended
                    DisplayWin2(result);
                }
            }
            else{
                // Display results once game has ended
                DisplayWin2(result);
            }
            // Break out of case
            break;
        case 3:  /* One Player Mode: Medium (against continual learning Linear Regression Neural Network ML Model) */
            // Get the features and score of the current board before the first player's move
            getBoardFeatures(board, base_player);                                   // Get pre-move board features for the base player
            starting_score_player = evaluateBoard(board_features, model_weights);   // Get pre-move board score
            // Make a copy of the current board features before the first player's move
            for (int j = 0; j < NO_FEATURES; j++){
                starting_board_features_player[j] = board_features[j];
            }

            /* First Player's Move */
            gtk_button_set_label(button, "X");      // Change the button label
            CreateCSS(GTK_WIDGET(button),"xo");                 // Add CSS class to button
            audio(P1_SOUND);                                    // Play sound effect for Player 1
            move_index = GPOINTER_TO_INT(data);                 // Get the player's move
            board[move_index] = -1;                             // Set the player's move on the board
            gtk_widget_set_sensitive(GTK_WIDGET(button), 0);    // Set the button to be non clickable after the player's move

            // Check the board's status (win/lose/draw/in progress)
            result = checkWin();
            if(result == 0){ // Game still in progress
                // Get the features and score of the intermediate board, after the first player's move
                getBoardFeatures(board, base_player);                                       // Get intermediate board features for the base player
                intermediate_score_player = evaluateBoard(board_features, model_weights);   // Get intermediate board score
                // Update ML model's weights after intermediate board with first player's move
                updateWeights(learningRate, starting_board_features_player, model_weights, intermediate_score_player, starting_score_player); // intermediate_score (player) is the actual value, starting_score (player) is the predicted value

                // Get the features and score of the current board before the computer player's move
                getBoardFeatures(board, base_player);                               // Get pre-move board features for the base player
                starting_score_ai = evaluateBoard(board_features, model_weights);   // Get pre-move board score
                // Make a copy of the current board features before the computer player's move
                for (int j = 0; j < NO_FEATURES; j++){
                    starting_board_features_ai[j] = board_features[j];
                }

                /* ML Model's Move */
                int move = modelInput(model_weights, 1);        // Get ML Model's move
                delay(TIME_DELAY);                              // Wait for a set period of time before making the move
                board[move] = 1;                                // Set ML model's move
                GtkWidget *buttonChild = gtk_grid_get_child_at(GTK_GRID(boardGrid), ButtonPos[move][0], ButtonPos[move][1]);
                gtk_button_set_label(GTK_BUTTON(buttonChild), "O"); // Set the button text
                CreateCSS(buttonChild,"xo");            // Add CSS class to button
                audio(AI_SOUND);                                    // Play sound effect for Computer Player
                gtk_widget_set_sensitive(buttonChild, 0);           // Set the button to be non clickable after the computer's move
                
                // Check the board's status (win/lose/draw/in progress)
                result = checkWin();
                if(result != 0){ // End of game
                    // Set game results (2: Draw, -1: Player 1 won, 1: Player 2 won, 0: In progress)
                    if (result == 2){
                        game_result = 0; // Draw for Player 1
                    }
                    else if (result == -1){
                        game_result = 1; // Win for Player 1
                    }
                    else {
                        game_result = -1; // Loss for Player 1
                    }
                    // Get the post-game features and score after the computer player's move 
                    getBoardFeatures(board, base_player);                           // Get post-game board features for the base player
                    final_score_ai = evaluateBoard(board_features, model_weights);  // Get post-game board score
                    // Update ML model's weights after computer player's move that led to a game completion
                    updateWeights(learningRate, starting_board_features_ai, model_weights, game_result, final_score_ai); // game_result is the actual value, final_score (ai) is the predicted value

                    // Display results once game has ended
                    DisplayWin2(result);
                }
                else { // Game still in progress
                    // Get the features and score of the intermediate board, after the computer player's move
                    getBoardFeatures(board, base_player);                                   // Get intermediate board features for the base player
                    intermediate_score_ai = evaluateBoard(board_features, model_weights);   // Get intermediate board score
                    // Update ML model's weights after intermediate board with computer player's move
                    updateWeights(learningRate, starting_board_features_ai, model_weights, intermediate_score_ai, starting_score_ai); // intermediate_score (ai) is the actual value, starting_score (ai) is the predicted value
                }
            }
            else { // End of game
                // Set game results (2: Draw, -1: Player 1 won, 1: Player 2 won, 0: In progress)
                if (result == 2){
                    game_result = 0; // Draw for Player 1
                }
                else if (result == -1){
                    game_result = 1; // Win for Player 1
                }
                else {
                    game_result = -1; // Loss for Player 1
                }
                // Get the post-game features and score after the first player's move 
                getBoardFeatures(board, base_player);                               // Get post-game board features for the base player
                final_score_player = evaluateBoard(board_features, model_weights);  // Get post-game board score
                // Update ML model's weights after first player's move that led to a game completion
                updateWeights(learningRate, starting_board_features_player, model_weights, game_result, final_score_player); // game_result is the actual value, final_score (player) is the predicted value

                // Display results once game has ended
                DisplayWin2(result);
            }
            // Break out of case
            break;
        case 4:  /* One Player Mode: Hard (against Minimax Algorithm) */
            /* First Player's Move */
            gtk_button_set_label(button, "X");      // Change the button label
            CreateCSS(GTK_WIDGET(button),"xo");                 // Add CSS class to button
            audio(P1_SOUND);                                    // Play sound effect for Player 1
            move_index = GPOINTER_TO_INT(data);                 // Get the player's move
            board[move_index] = -1;                             // Set the player's move on the board
            gtk_widget_set_sensitive(GTK_WIDGET(button), 0);    // Set the button to be non clickable after the player's move

            // Check the board's status (win/lose/draw/in progress)
            result = checkWin();
            if(result == 0){ // Game still in progress
                /* MiniMax Algorithm's Move */
                int move = computerMove();          // Get MiniMax Algorithm's move
                delay(TIME_DELAY);                  // Wait for a set period of time before making the move
                board[move] = 1;                    // Set MiniMax Algorithm's move
                GtkWidget *buttonChild = gtk_grid_get_child_at(GTK_GRID(boardGrid), ButtonPos[move][0], ButtonPos[move][1]);
                gtk_button_set_label(GTK_BUTTON(buttonChild), "O"); // Set the button text
                CreateCSS(GTK_WIDGET(buttonChild),"xo");            // Add CSS class to button
                audio(AI_SOUND2);                                   // Play sound effect for Computer Player
                gtk_widget_set_sensitive(buttonChild, 0);           // Set the button to be non clickable after the computer's move
                
                // Check the board's status (win/lose/draw/in progress)
                result = checkWin();
                if(result != 0){
                    // Display results once game has ended
                    DisplayWin2(result);
                }
            }
            else{
                // Display results once game has ended
                DisplayWin2(result);
            }
            // Break out of case
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
void DisplayWin(int result){

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
void DisplayWin2(int result){

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