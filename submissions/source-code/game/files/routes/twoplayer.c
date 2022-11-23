#include <gtk/gtk.h>                // Include GTK library for GUI
#include "../header/config.h"       // Include configuration file

/* Two Player Mode Function */
void twoplayer(GtkButton *button, int data){
    int pos = data;

    if(player == -1){ // First Player
        audio(P1_SOUND);                                                    // Play sound effect for first player
        gtk_label_set_markup(GTK_LABEL(gtk_button_get_child(button)), 
                             "<span color=\"#ffb300\">X</span>");           // Set X on board
        board[pos] = -1;                                                    // Update the global board
        gtk_widget_set_sensitive(GTK_WIDGET(button), 0);                    // Set the button to be non clickable after the move
        gtk_label_set_markup(GTK_LABEL(turnLabel), 
                    "<span color=\"#87dcfa\" size=\"16pt\">O's\n</span><span color=\"slategrey\" size=\"16pt\">Turn</span>");       
        gtk_label_set_justify(GTK_LABEL(turnLabel), GTK_JUSTIFY_CENTER);    // Change the turnLabel
        player = 1;                                                         // Change to the next player (Player 2)
    }
    else if(player == 1){ // Second Player
        audio(P2_SOUND);                                                    // Play sound effect for the second player
        gtk_label_set_markup(GTK_LABEL(gtk_button_get_child(button)),
                            "<span color=\"#87dcfa\">O</span>");
        board[pos] = 1;                                                     // Update the global board
        gtk_label_set_markup(GTK_LABEL(turnLabel), 
                    "<span color=\"#ffb300\" size=\"16pt\">X's\n</span><span color=\"slategrey\" size=\"16pt\">Turn</span>");       
        gtk_label_set_justify(GTK_LABEL(turnLabel), GTK_JUSTIFY_CENTER);    // Change the turnLabel
        gtk_widget_set_sensitive(GTK_WIDGET(button), 0);                    // Set the button to be non clickable after the move
        player = -1;                                                        // Change to the next player (Player 1)
    }
}