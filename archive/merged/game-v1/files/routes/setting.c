#include <gtk/gtk.h>                // Include GTK library for GUI
#include "../header/config.h"       // Include configuration file

//Global Vars for Settings
const char *gamemode[] = { "\nPLEASE SELECT A GAME MODE\n", "\n TWO PLAYER MODE\n", "\nONE PLAYER MODE (EASY)\n", "\nONE PLAYER MODE (MEDIUM)\n", "\nONE PLAYER MODE (HARD)\n"};
GtkWidget *settingGrid, *StartBtn, *gameModeMenu;

//Create the design of the Settings Bar
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
    const char *mode[] = { "\nPLEASE SELECT A GAME MODE\n", "\n TWO PLAYER MODE\n", "\nONE PLAYER MODE (EASY)\n", "\nONE PLAYER MODE (MEDIUM)\n", "\nONE PLAYER MODE (HARD)\n", NULL };
    gameModeMenu = gtk_drop_down_new_from_strings(gamemode);
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
void modeController(GtkDropDown  *dropdown, gpointer *data){

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
            gtk_label_set_text(GTK_LABEL(headerlabel), gamemode[id]);
            //Change the Start button to start
            gtk_button_set_label(GTK_BUTTON(StartBtn), "RESTART");
            //Refresh the board
            Restart();
        }
    }

}

// Start function
void Start(GtkWidget *widget, gpointer *data){
    //Get the Current Text of the button
    const char *btnText = gtk_button_get_label(GTK_BUTTON(widget));
    GtkWidget* buttonChild;
    if(gameModeOption != -1 && gameModeOption != 0){
        if(strcmp(btnText,"START") == 0){
            //If btn is Start
            //Set the header  Label to selected game mode
            gtk_label_set_text(GTK_LABEL(headerlabel), gamemode[gameModeOption]);
            //Set button to Restart
            gtk_button_set_label(GTK_BUTTON(widget), "RESTART");
            
            //Set the board to be playable
            Restart();
        }else if(strcmp(btnText,"RESTART") == 0){
            //Refresh the board
            Restart();
            //Set the HeaderLabel
            gtk_label_set_text(GTK_LABEL(headerlabel), gamemode[gameModeOption]);
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
        CreateCSS((buttonChild),"xo");
        //Reset the board var 
        board[i]=0; 
        //Allow Clicking         
        gtk_widget_set_sensitive(buttonChild, 1);
    }
    //Set back to player 1 start first
    player = -1;
}