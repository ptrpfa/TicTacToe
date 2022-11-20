#include <gtk/gtk.h>                // Include GTK library for GUI
#include "../header/config.h"       // Include configuration file

//Global var
GtkWidget *window, *headerLabel;

/* GTK GUI Functions */
// Function to initialise GTK elements
void activate(GtkApplication* app, gpointer user_data){

    /*Window Creation*/
    window = gtk_application_window_new(app);                          //Create the window
    gtk_window_set_title( GTK_WINDOW(window), "Tic Tac Toe");          //Set Window Title
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 760);        //Set Window Size
    CreateCSS(window, NULL);                                           //Windows CSS
    /*Window Creation*/

    //Init MiniAudio
    miniaudio_init();

    DesignModel();
    gtk_widget_show(window);
}

// Design Model for GUI
void DesignModel(){
    GtkWidget *box;             //Parent Container for all widgets

    //** Box Designs **//
    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0); 
    gtk_window_set_child (GTK_WINDOW (window), box); //Adds the box to the GUI

    headerLabel = gtk_label_new("\nWelcome to Tic Tac Toe!\n"); //Create header label
    CreateCSS(headerLabel, "headerlabel");                      //Style the label
    //Add Label to box
    gtk_box_append(GTK_BOX(box), (headerLabel));
    gtk_widget_set_halign (headerLabel, GTK_ALIGN_CENTER);      //Horizontal alignment
    gtk_widget_set_valign (headerLabel, GTK_ALIGN_CENTER);      //Vertical alignment

    //Create the Settings field
    SettingDesign();

    //Create the playing field
    BoardDesign(); 

    //Create the scoreboard field
    Scoreboard();

    //Add all widget to the box
    gtk_box_append(GTK_BOX(box), (settingGrid));
    gtk_box_append (GTK_BOX (box), (boardGrid));
    gtk_box_append (GTK_BOX (box), (scoreGrid));
    //** Box Designs **//
}