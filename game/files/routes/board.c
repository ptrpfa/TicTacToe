#include <gtk/gtk.h>                // Include GTK library for GUI
#include "../header/config.h"       // Include configuration file

//Global Var
GtkWidget *boardGrid; 
int board[9] = {0,0,0,0,0,0,0,0,0};
int ButtonPos[9][2] = {{0,0},{160,0},{320,0}, {0,160},{160,160},{320,160}, {0,320},{160,320},{320,320}}; 

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
