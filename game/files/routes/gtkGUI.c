#include <gtk/gtk.h>                // Include GTK library for GUI
#include "../header/config.h"       // Include configuration file

//Global var
GtkWidget *window, *headerlabel;

/* GTK GUI Functions */
// Function to initialise GTK elements
void activate(GtkApplication* app, gpointer user_data){

    /*Window Creation*/
    window = gtk_application_window_new(app);
    gtk_window_set_title( GTK_WINDOW(window), "Tic Tac Toe"); //Set Window Title
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 750); 
    /*End Window Creation*/

    //Init MiniAudio
    miniaudio_init();

    //CSS
    CreateCSS(window, NULL);

    Designer();
    gtk_widget_show(window);
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
    gtk_box_append(GTK_BOX(box), (headerlabel));
    gtk_widget_set_halign (headerlabel, GTK_ALIGN_CENTER); //Horizontal alignment
    gtk_widget_set_valign (headerlabel, GTK_ALIGN_CENTER); //Vertical alignment
    
    //Create the playing field
    BoardDesign();   
    //Create the Settings field
    SettingDesign();
    
    //Add all widget to the box
    gtk_box_append(GTK_BOX(box), (settingGrid));
    gtk_box_append (GTK_BOX (box), (boardGrid));
}