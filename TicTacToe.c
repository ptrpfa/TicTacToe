//Tic Tac Toe GUI
//Two Player Mode
#include <gtk/gtk.h>
#include <stdio.h>

/*Widgets*/
GtkWidget* window;
GtkWidget* headerlabel;
GtkWidget* boardGrid;
GtkWidget* settingGrid;

/*Tic Tac Toe Button Position*/
int ButtonPos[9][2] = {{0,0},{20,0},{40,0},
                       {0,20},{20,20},{40,20},
                       {0,40},{20,40},{40,40}}; //{column, row} for 20 by 20 box

/*Game Controller*/
static int player = 1; //tracks current player
int board[9]; //All element will be 0 at start

const char * array[3] = {"2 Player", "1 VS Computer(Minimax)", "1 VS Computer(ML)"};
int checkPlayerData(char n){
    if('X' == n){
        return 1; //Player 1
    }else if('O' == n){
        return 2; //Player 2
    }else{
        return 0; //Empty
    }
}

int checkWin(){

    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}}; //Positions to win

    for(int i = 0; i < 8; ++i) {
        if(board[wins[i][0]] != 0 && //Check if empty, '0' is empty
           board[wins[i][0]] == board[wins[i][1]] && //Check if first of element of the condition above is eql to to second element 
           board[wins[i][0]] == board[wins[i][2]]){ //Check if first element of the condition above is eql to the third element 
            return board[wins[i][2]]; //All condition fufill, return the winner character ('1' or '2')
        }
    }
    return 0; //Else no one win returns '0'
}

static void MainGameController(GtkWidget *button, gpointer data){

    //Set the correct Label for the player on press button
    if(player == 1){
        //First Player
        //Change the button label
        gtk_button_set_label(GTK_BUTTON(button), "X");
        //Update the global board;
        int pos = GPOINTER_TO_INT(data);
        board[pos] = 1;
        //Set the button to be non clickable
        gtk_widget_set_sensitive(button, 0); 
        player = 2; //set for player 2
    }else if(player = 2){
        //Second Player
        //Change the button label
        gtk_button_set_label(GTK_BUTTON(button), "O");
        //Update the global board;
        int pos = GPOINTER_TO_INT(data);
        board[pos] = 2;
        //Set the button to be non clickable
        gtk_widget_set_sensitive(button, 0); 
        player = 1; //Set for player 1
    }

    int result = checkWin();

    GtkWidget* buttonChild;

    switch(result){
        case 0:
            //Check if all button is pressed
            for(int i =0; i < 9; i++){
                if(board[i] == 0){
                    break;
                }
                if(i == 8){
                    gtk_label_set_text(GTK_LABEL(headerlabel), "Its a draw! Try Again lah...");
                }
            }
            break;
        case 1:
            gtk_label_set_text(GTK_LABEL(headerlabel), "Player 1, You win! Inconceivable!");
            //Make board unclickable till restart button is clicked
            for(int i=0; i < 9;i++){
                buttonChild = gtk_grid_get_child_at(GTK_GRID(boardGrid), ButtonPos[i][0], ButtonPos[i][1]);
                gtk_widget_set_sensitive(buttonChild, 0);
            }
            break;
        case 2:
            gtk_label_set_text(GTK_LABEL(headerlabel), "Player 2, You win! Inconceivable!");
            for(int i=0; i < 9;i++){
                buttonChild = gtk_grid_get_child_at(GTK_GRID(boardGrid), ButtonPos[i][0], ButtonPos[i][1]);
                gtk_widget_set_sensitive(buttonChild, 0);
            }
            break;
    }
}

void BoardDesign(){
    /* Here we construct the grid that is going pack our buttons */ 
    GtkWidget* button;
    boardGrid = gtk_grid_new (); 
    gtk_grid_set_column_homogeneous(GTK_GRID(boardGrid),TRUE); 
    gtk_grid_set_row_homogeneous(GTK_GRID(boardGrid),TRUE); 
    gtk_widget_set_halign (boardGrid, GTK_ALIGN_CENTER); //Horizontal alignment
    gtk_widget_set_valign (boardGrid, GTK_ALIGN_CENTER); //Vertical alignment

    for(int i=0; i < 9; i++){
      button = gtk_button_new_with_label(" "); //Set button name
      g_signal_connect(button, "clicked", G_CALLBACK (MainGameController), GINT_TO_POINTER(i));// (gpointer)i gives the current position of the button
      gtk_grid_attach (GTK_GRID (boardGrid), button, ButtonPos[i][0], ButtonPos[i][1], 20, 20);
    }

}

void Restart(){

}

static void Combo (GtkWidget* widget, gpointer *data){
    // char* text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widget));
    // printf("%c", *text);
    // guint itemPos = gtk_drop_down_get_selected(GTK_DROP_DOWN(widget));
    // char *hello = array[itemPos];
    // printf("%c", *hello);
    printf("hello");
}

void SettingDesign(){
    GtkWidget * RestartBtn;
    GtkWidget * QuitBtn;

    settingGrid = gtk_grid_new();
    //Set alignment
    gtk_grid_set_column_homogeneous(GTK_GRID(boardGrid),TRUE); 
    gtk_grid_set_row_homogeneous(GTK_GRID(boardGrid),TRUE); 

    RestartBtn = gtk_button_new_with_label ("Restart"); //Set button name
    
    // /*This is for connecting to css and creating design for the buttons or widgets*/
    // openContext = gtk_widget_get_style_context(RestartBtn);
    // provider = gtk_css_provider_new();
    // gtk_css_provider_load_from_path(provider, "styles.css");
    //     //Initialize providers
    // //Add context providers and attach CSS
    // gtk_style_context_add_provider(openContext, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    // /*End of CSS */

    g_signal_connect (RestartBtn, "clicked", G_CALLBACK (Restart), NULL); //prints to command line when clicked
    gtk_grid_attach (GTK_GRID (settingGrid), RestartBtn, 1, 0, 1, 1);

    
    GtkWidget* dropMenu;

    //Init the Menu
    dropMenu = gtk_combo_box_text_new();
    
    //Populate the Menu
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(dropMenu), NULL, "2 Player");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(dropMenu), NULL, "1 VS Computer(Minimax)");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(dropMenu), NULL, "1 VS Computer(ML)");
    gtk_combo_box_set_active(GTK_COMBO_BOX(dropMenu), 0);

    //On Change of options
    g_signal_connect (dropMenu, "changed", G_CALLBACK (Combo), NULL);
    gtk_grid_attach(GTK_GRID (settingGrid), dropMenu, 2,  0, 3, 1);

    QuitBtn = gtk_button_new_with_label ("Quit"); //Set button name
    g_signal_connect_swapped (QuitBtn, "clicked", G_CALLBACK (gtk_window_destroy), window); 
    gtk_grid_attach (GTK_GRID (settingGrid), QuitBtn, 6,  0, 1, 1);

}

void Designer(){

    GtkWidget *box;
    /*Start of box design to hold all widgets*/
    //Create a contianer box which contains tic tac toe grid
    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0); 
    gtk_window_set_child (GTK_WINDOW (window), box); //Adds the widget to the GUI

    //Create a Dialog Label
    headerlabel = gtk_label_new("Lets Play Tic Tac Toe meows~");
    //Add Label to box
    gtk_box_append(GTK_BOX(box), GTK_LABEL(headerlabel));
    gtk_widget_set_halign (headerlabel, GTK_ALIGN_CENTER); //Horizontal alignment
    gtk_widget_set_valign (headerlabel, GTK_ALIGN_CENTER); //Vertical alignment

    //Create the board
    BoardDesign();
    //Add the board to box
    gtk_box_append (GTK_BOX (box), boardGrid); 

    SettingDesign();
    gtk_box_append(GTK_BOX(box), settingGrid);
}

static void activate(GtkApplication* app, gpointer user_data){

    /*Window Creation*/
    window = gtk_application_window_new(app);
    gtk_window_set_title( GTK_WINDOW(window), "Meow Meow"); //Set Window Title
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500); //Set Window Size
    /*End Window Creation*/
    Designer();
    gtk_widget_show(window);
}

int main(int argc, char**argv){

  //Create a GTKApplication object
  GtkApplication* app; //app is the GTKApplicaiton 
  int status;

  app = gtk_application_new(NULL, G_APPLICATION_DEFAULT_FLAGS); //Init App, Parameter: application name, flags for special needs 
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);//Connect App with the 'activate' function, or the settings for the GUI
  status = g_application_run(G_APPLICATION(app), argc, argv); //Accpets command line argument with argc and argv
  g_object_unref(app); //Remove it from memory
  //End of Creation

  return status;
}
