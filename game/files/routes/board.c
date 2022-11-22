#include <gtk/gtk.h>                // Include GTK library for GUI
#include "../header/config.h"       // Include configuration file

//Global Var
GtkWidget *boardGrid; 
int board[9] = {0,0,0,0,0,0,0,0,0};
int ButtonPos[9][2] = {{0,0},{140,0},{280,0}, {0,140},{140,140},{280,140}, {0,280},{140,280},{280,280}}; 

void BoardDesign(){                                                   // Create the Design for the Tic Tac Toe Board

    //** Board Design**//
    GtkWidget* button;
    boardGrid = gtk_grid_new (); 
    gtk_grid_set_column_homogeneous(GTK_GRID(boardGrid),TRUE); 
    gtk_grid_set_row_homogeneous(GTK_GRID(boardGrid),TRUE); 
    gtk_widget_set_halign (boardGrid, GTK_ALIGN_CENTER);              //Horizontal alignment
    gtk_widget_set_valign (boardGrid, GTK_ALIGN_CENTER);              //Vertical alignment

    // Init the board
    for(int i=0; i < 9; i++){ 
        button = gtk_button_new_with_label(NULL); 
        g_signal_connect(button, "clicked", G_CALLBACK (MainGameController), GINT_TO_POINTER(i)); // (gpointer)i gives the current position of the button
        CreateCSS(button, "boardbtn");
        gtk_widget_set_tooltip_text(button, "Please select gamemode to start");
        gtk_grid_attach (GTK_GRID (boardGrid), button, ButtonPos[i][0], ButtonPos[i][1], 140, 140);
    }
    //** Board Design**//
}