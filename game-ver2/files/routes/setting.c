#include <gtk/gtk.h>                // Include GTK library for GUI
#include "../header/config.h"       // Include configuration file

//Global Vars for Settings
const char *gamemode[] = { "\nPLEASE SELECT A GAME MODE\n", 
                           "\n TWO PLAYER MODE\n", 
                           "\nONE PLAYER MODE (EASY)\n", 
                           "\nONE PLAYER MODE (MEDIUM)\n", 
                           "\nONE PLAYER MODE (HARD)\n"};

GtkWidget *settingGrid, *gameModeMenu, *StartBtn, *turnLabel;

//Create the design of the Settings Bar
void SettingDesign(){

    //** Setting Design **//
    settingGrid = gtk_grid_new();                                               //Grid Init
    //Set alignment
    CreateCSS(settingGrid, "setting_grid");
    gtk_widget_set_halign (settingGrid, GTK_ALIGN_CENTER); 
    gtk_widget_set_valign (settingGrid, GTK_ALIGN_CENTER);
    gtk_grid_set_column_spacing(GTK_GRID (settingGrid), 50);                    //Set each widget spacing
                                                     
    turnLabel = gtk_label_new(NULL);                                            //Indicate which player's turn
    gtk_label_set_markup(GTK_LABEL(turnLabel), 
                        "<span color=\"#ffb300\">X</span><span color=\"#87dcfa\">O</span>");          

    CreateCSS(turnLabel, "turnlabel");
    gtk_grid_attach (GTK_GRID (settingGrid), turnLabel, 2, 0, 2, 2);            //Set to Grid

    //Dropdown box
    gameModeMenu = gtk_drop_down_new_from_strings(gamemode);
    g_signal_connect(gameModeMenu, "notify::selected", G_CALLBACK (modeController), NULL);
    CreateCSS(gameModeMenu, "dropdown");
    gtk_grid_attach (GTK_GRID (settingGrid), gameModeMenu, 6, 0, 8, 1);
    //Dropdown Box

    //Start or Restart Button in the grid (to restart the game) or (to start the game)
    StartBtn = gtk_button_new_with_label ("START");                             //Set button name
    g_signal_connect(StartBtn, "clicked", G_CALLBACK(Start), NULL); 
    GdkCursor* nope = gdk_cursor_new_from_name("not-allowed", NULL);            //Set Cursor for StartBtn
    gtk_widget_set_cursor(StartBtn, nope);
    CreateCSS(StartBtn, "startbtn");
    gtk_grid_attach (GTK_GRID (settingGrid), StartBtn, 15, 0, 3, 1);

    //** Setting Design **//
}

// Function for controlling the game mode selection
void modeController(GtkDropDown  *dropdown, gpointer *data){

    guint id = gtk_drop_down_get_selected (dropdown);
    if(id != 0){                                                                    //If one of the gameMode is selected
        GdkCursor* point = gdk_cursor_new_from_name("pointer", NULL);               //Reset StartBtn Cursor Pointer
        gtk_widget_set_cursor(StartBtn, point);
        gameModeOption = id;                                                        //Set Global gamemode option to selected
        const char *btnText = gtk_button_get_label(GTK_BUTTON(StartBtn));
        if(strcmp(btnText,"RESTART") == 0){
            gtk_label_set_text(GTK_LABEL(headerLabel), gamemode[gameModeOption]);   //Change the headerLabel to gamemode
        }
        Restart();
        SetScore(0); //Game-In-Progress
    }else{
        GdkCursor* nope = gdk_cursor_new_from_name("not-allowed", NULL);            //Set Cursor for StartBtn
        gtk_widget_set_cursor(StartBtn, nope);
        gameModeOption = -1;
    }   

}

// Start function
void Start(GtkWidget *startbtn, gpointer *data){
    const char *btnText = gtk_button_get_label(GTK_BUTTON(startbtn));
    if(gameModeOption != -1){
        gtk_label_set_text(GTK_LABEL(headerLabel), gamemode[gameModeOption]);       //Change the headerLabel to gamemode

        if(strcmp(btnText,"START") == 0){
            gtk_button_set_label(GTK_BUTTON(startbtn), "RESTART");                  //Change the StartBtn text to 'restart'
        }

        gtk_label_set_markup(GTK_LABEL(turnLabel), 
                            "<span color=\"#ffb300\" size=\"16pt\">X's\n</span><span color=\"slategrey\" size=\"16pt\">Turn</span>");       //Change the turnLabel
        gtk_label_set_justify(GTK_LABEL(turnLabel), GTK_JUSTIFY_CENTER);
        Restart();
    }
}

// Restart function
void Restart(){
    GtkWidget* buttonChild;
    for(int i=0;i<9;i++){
        buttonChild = gtk_grid_get_child_at(GTK_GRID(boardGrid), ButtonPos[i][0], ButtonPos[i][1]);
        gtk_button_set_label(GTK_BUTTON(buttonChild), NULL);                        //Reset the button text
        gtk_widget_set_sensitive(buttonChild, 1);
        board[i]=0;                                                                 //Reset the board var          
        gtk_widget_set_tooltip_text(buttonChild, NULL);
    }
    player = -1;                                                                    //Set back to player 1 start first
}