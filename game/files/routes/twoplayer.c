#include <gtk/gtk.h>                // Include GTK library for GUI
#include "../header/config.h"       // Include configuration file

/* Two Player Mode Function */
// Function to get the users' inputs for 2 Player Mode
void twoplayer(GtkButton *button, int data){
    // Set the correct Label for the player on press button
    if(player == -1){ // First Player
        // Play sound effect for first player
        audio(P1_SOUND);
        // Change the button label
        gtk_button_set_label(button, "X");
        CreateCSS(GTK_WIDGET(button),"xo");
        // Update the global board;
        int pos = data;
        board[pos] = -1;
        // Set the button to be non clickable after the move
        gtk_widget_set_sensitive(GTK_WIDGET(button), 0); 
        player = 1; // Change to the next player (Player 2)
    }
    else if(player == 1){ // Second Player
        // Play sound effect for the second player
        audio(P2_SOUND);
        // Change the button label
        gtk_button_set_label(button, "O");
        CreateCSS(GTK_WIDGET(button),"xo");
        // Update the global board
        int pos = data;
        board[pos] = 1;
        // Set the button to be non clickable after the move
        gtk_widget_set_sensitive(GTK_WIDGET(button), 0); 
        player = -1; // Change to the next player (Player 1)
    }
}