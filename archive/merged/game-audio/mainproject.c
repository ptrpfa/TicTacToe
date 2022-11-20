//work in progress - gui

//Tic Tac Toe GUI
//Two Player Mode
#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

/*Widgets*/
GtkWidget* window;

GtkWidget* headerlabel;

GtkWidget* boardGrid;

GtkWidget* settingGrid, *StartBtn, *gameModeMenu;

/*Game mode */
int gameModeOption = -1;
const char *gamemodeLabel[] = { "\nPLEASE ENTER A GAME MODE\n", 
                        "\nMULTIPLAYER\n", 
                        "\nPLAYER VS COMPUTER(HARD)\n", 
                        "\nPLAYER VS COMPUTER(MEDIUM)\n"};

/*Tic Tac Toe Button Position*/
int ButtonPos[9][2] = {{0,0},{160,0},{320,0},
                       {0,160},{160,160},{320,160},
                       {0,320},{160,320},{320,320}};  

/*Game Controller*/
static int player = -1; //tracks current player
int board[9] = {0,0,0,0,0,0,0,0,0}; //All element will be 0 at start 

/*Functions Prototype*/
static void activate(GtkApplication* app, gpointer user_data);
void CreateCSS(GtkWidget *widget, const char *class_name);
void Designer();
/*For Setting*/
void SettingDesign();
static void modeController(GtkDropDown  *dropdown, gpointer *data);
static void Start(GtkWidget *widget, gpointer *data);
void Restart();
/*For Board*/
void BoardDesign();
/*For Board Logic*/
int checkWin();
int audio();
int DisplayWin(int result);
int checkPlayerData(char n);
static void MainGameController(GtkButton *button, gpointer data);

void twoplayer(GtkButton *button, int data); //2-Player
int computerMove();//MiniMax
int minimax(int player); //MiniMax
/*End Function Prototype*/


int audio (const char *file, double duration ){

    if (!al_init()){
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    if (!al_install_audio()){
        fprintf(stderr, "failed to initialize audio!\n");
        return -1;
    }

    if (!al_init_acodec_addon()){
        fprintf(stderr, "failed to initialize audio codecs!\n");
        return -1;
    }

    if (!al_reserve_samples(1)){
        fprintf(stderr, "failed to reserve samples!\n");
        return -1;
    }

    al_install_audio();
    al_init_acodec_addon();

    ALLEGRO_SAMPLE *sample = al_load_sample(file); //sample always NULL

    al_reserve_samples(1);

    if (!sample){
        printf("Audio clip sample not loaded!\n");
        return -1;
    }

    /* Loop the sample until the display closes. */
    al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

    al_rest(duration);
    al_destroy_sample(sample);
    return 0;
}

int main(int argc, char**argv){

  //Create a GTKApplication object
  GtkApplication* app; //app is the GTKApplication 
  int status;

  app = gtk_application_new(NULL, G_APPLICATION_DEFAULT_FLAGS); //Init App, Parameter: application name, flags for special needs 
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);//Connect App with the 'activate' function, or the settings for the GUI
  status = g_application_run(G_APPLICATION(app), argc, argv); //Accpets command line argument with argc and argv
  g_object_unref(app); //Remove it from memory
  //End of Creation

  return status;
}

static void activate(GtkApplication* app, gpointer user_data){

    /*Window Creation*/
    window = gtk_application_window_new(app);
    gtk_window_set_title( GTK_WINDOW(window), "TIC TAC TOE"); //Set Window Title

    gtk_window_set_default_size(GTK_WINDOW(window), 1250, 1000); //Set Window Size
    /*End Window Creation*/

    //CSS
    CreateCSS(window, NULL);

    Designer();
    gtk_widget_show(window);
}

void CreateCSS(GtkWidget *widget, const char *class_name){
    GtkCssProvider *provider2;
    GtkStyleContext *context2;

    //Init CSS
    context2 = gtk_widget_get_style_context(widget);
    provider2 = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider2, "styles.css");
    gtk_style_context_add_provider(context2, GTK_STYLE_PROVIDER(provider2), GTK_STYLE_PROVIDER_PRIORITY_USER);

    //Create Class
    if(class_name != NULL){
        gtk_style_context_add_class(context2, class_name);
    }

}

//Design COntroller for GUI
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

//Create the design for Setting bar
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
    gtk_widget_set_sensitive(GTK_BUTTON(StartBtn), 0); //Set Unclickable
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
    gtk_grid_attach (GTK_GRID (settingGrid), QuitBtn, 6,  0, 1, 1);

    //Create CSS for StartBtn and QuitBtn and SettingGrid
    CreateCSS(settingGrid, "setting_grid");
    CreateCSS(StartBtn, "start_btn");
    CreateCSS(QuitBtn, "quit_btn");
}

static void modeController(GtkDropDown  *dropdown, gpointer *data){

    guint id = gtk_drop_down_get_selected (dropdown);
    if(gameModeOption == -1){ //Game just started 
        if(id != 0){
            //If one of the gameMode is selected
            //Set StartBtn to clickable
            gtk_widget_set_sensitive(GTK_BUTTON(StartBtn), 1);
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

static void Start(GtkWidget *widget, gpointer *data){
    //Get the Current Text of the button
    const char *btnText = gtk_button_get_label(GTK_BUTTON(widget));
    GtkWidget* buttonChild;

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
    player =-1;
}

//Create the Design for the Tic Tac Toe Board
void BoardDesign(){
    /* Here we construct the grid that is going pack our buttons */ 
    GtkWidget* button;
    boardGrid = gtk_grid_new (); 
    gtk_grid_set_column_homogeneous(GTK_GRID(boardGrid),TRUE); 
    gtk_grid_set_row_homogeneous(GTK_GRID(boardGrid),TRUE); 
    gtk_widget_set_halign (boardGrid, GTK_ALIGN_CENTER); //Horizontal alignment
    gtk_widget_set_valign (boardGrid, GTK_ALIGN_CENTER); //Vertical alignment
    
    for(int i=0; i < 9; i++){ 
        GtkWidget* button;
        button = gtk_button_new_with_label(" "); //Set button name
        g_signal_connect(button, "clicked", G_CALLBACK (MainGameController), GINT_TO_POINTER(i));// (gpointer)i gives the current position of the button
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

int checkWin(){

    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}}; //Positions to win

    for(int i = 0; i < 8; ++i) {
        if(board[wins[i][0]] != 0 && //Check if empty, '0' is empty
           board[wins[i][0]] == board[wins[i][1]] && //Check if first of element of the condition above is eql to to second element 
           board[wins[i][0]] == board[wins[i][2]]){ //Check if first element of the condition above is eql to the third element 
            return board[wins[i][2]]; //All condition fufill, return the winner character ('-1' or '1')
        }
    }
    //Check for draw
    for(int i =0; i < 9; i++){
        if(board[i] == 0){
            return 0; //Else no one win returns '0'
        }
        if(i == 8){
            return 2; //Draw
        }
    }
}

int DisplayWin(int result){

    GtkWidget* buttonChild;
    switch(result){
        case 2:
            gtk_label_set_text(GTK_LABEL(headerlabel), "\nIT'S A DRAW!\n");
            audio("sound/tadang.wav",0.8);
            break;
        case -1:
            gtk_label_set_text(GTK_LABEL(headerlabel), "\nPLAYER 1 WINS!\n");
            //Make board unclickable till restart button is clicked
            for(int i=0; i < 9;i++){
                buttonChild = gtk_grid_get_child_at(GTK_GRID(boardGrid), ButtonPos[i][0], ButtonPos[i][1]);
                gtk_widget_set_sensitive(buttonChild, 0);
            }
            audio("sound/winner.wav",0.8);
            break;
        case 1:
            gtk_label_set_text(GTK_LABEL(headerlabel), "\nPLAYER 2 WINS!\n");
            for(int i=0; i < 9;i++){
                buttonChild = gtk_grid_get_child_at(GTK_GRID(boardGrid), ButtonPos[i][0], ButtonPos[i][1]);
                gtk_widget_set_sensitive(buttonChild, 0);
            }
            audio("sound/winner.wav",0.8);
            break;
    }

}

int DisplayWin2(int result){

    GtkWidget* buttonChild;
    switch(result){
        case 2:
            gtk_label_set_text(GTK_LABEL(headerlabel), "\nIT'S A DRAW\n");
            audio("sound/tadang.wav",0.8);
            break;
        case -1:
            gtk_label_set_text(GTK_LABEL(headerlabel), "\nPLAYER 1 WINS!\n");
            //Make board unclickable till restart button is clicked
            for(int i=0; i < 9;i++){
                buttonChild = gtk_grid_get_child_at(GTK_GRID(boardGrid), ButtonPos[i][0], ButtonPos[i][1]);
                gtk_widget_set_sensitive(buttonChild, 0);
            }
            audio("sound/winner.wav",0.8);
            break;
        case 1:
            gtk_label_set_text(GTK_LABEL(headerlabel), "\n YOU LOST!\n");
            for(int i=0; i < 9;i++){
                buttonChild = gtk_grid_get_child_at(GTK_GRID(boardGrid), ButtonPos[i][0], ButtonPos[i][1]);
                gtk_widget_set_sensitive(buttonChild, 0);
            }
            audio("sound/gameover.wav",0.8);
            break;
    }

}

int checkPlayerData(char n){
    if('X' == n){
        return -1; //Player 1
    }else if('O' == n){
        return 1; //Player 2
    }else{
        return 0; //Empty
    }
}

static void MainGameController(GtkButton *button, gpointer data){    

    int result = 0;
    switch(gameModeOption){
        case 1: //2 Player
            twoplayer(button, GPOINTER_TO_INT(data));
            result = checkWin();
            if(result !=0){ //Someone win or draw
                DisplayWin(result);
            } 
            break;

        case 2: //MiniMax
            //First Player
            //Change the button label
            gtk_button_set_label(GTK_WIDGET(button), "X");
            CreateCSS(GTK_WIDGET(button),"xo");
            audio("sound/biu.wav",0.8);
            //Update the global board;
            int pos = GPOINTER_TO_INT(data);
            board[pos] = -1;
            //Set the button to be non clickable
            gtk_widget_set_sensitive(GTK_WIDGET(button), 0);
            //End of first player
            //Check Win
            result = checkWin();
            if(result == 0){ //No one win
                //2nd Player Move
                int move = computerMove();
                board[move] = 1;            // AI played the best move 
                GtkWidget *buttonChild = gtk_grid_get_child_at(GTK_GRID(boardGrid), ButtonPos[move][0], ButtonPos[move][1]);
                //Set the button text
                gtk_button_set_label(GTK_BUTTON(buttonChild), "O");
                CreateCSS(GTK_BUTTON(buttonChild),"xo");
                audio("sound/biu.wav",0.8);
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

        case 3: //ML
            break;
    }
}

void twoplayer(GtkButton *button, int data){
    //Set the correct Label for the player on press button
    if(player == -1){
        //First Player
        //Change the button label
        audio("sound/biu.wav",0.8);
        gtk_button_set_label(GTK_WIDGET(button), "X");
        CreateCSS(GTK_WIDGET(button),"xo");
        //Update the global board;
        int pos = data;
        board[pos] = -1;
        //Set the button to be non clickable
        gtk_widget_set_sensitive(GTK_WIDGET(button), 0); 
        player = 1; //set for player 2
    }else if(player = 1){
        //Second Player
        //Change the button label
        audio("sound/biu.wav",0.8);
        gtk_button_set_label(GTK_WIDGET(button), "O");
        CreateCSS(GTK_WIDGET(button),"xo");
        //Update the global board;5
        int pos = data;
        board[pos] = 1;
        //Set the button to be non clickable
        gtk_widget_set_sensitive(GTK_WIDGET(button), 0); 
        player = -1; //Set for player 1
    }
}

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

//minimax algorithm//
int minimax(int player) { //P vs Minimax
    //How is the position like for player (their turn) on board?
    int winner = checkWin(board);        // getting the output from checkwinner func, '0' for no winner 
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