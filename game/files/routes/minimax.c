#include <gtk/gtk.h>                // Include GTK library for GUI
#include "../header/config.h"       // Include configuration file

// MiniMax algorithm
int minimax(int player) { //P vs Minimax
    //How is the position like for player (their turn) on board?
    int winner = checkWin();        // getting the output from checkwinner func, '0' for no winner 
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