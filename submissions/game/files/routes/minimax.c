#include <gtk/gtk.h>                // Include GTK library for GUI
#include "../header/config.h"       // Include configuration file

/* Minimax Algorithm Functions */
// MiniMax algorithm
int minimax(int player) { 
    int winner = checkWin();                        // getting the output from checkwinner func, '0' for no winner 
    if(winner != 0)                                 // checking if theres winner 
        return winner*player;                       // return if theres winner 
    
    int move = -1;
    int score = -2;                                 //Losing moves are preferred to no move
    int i;
    for(i = 0; i < 9; ++i) {                        //For all moves,
        if(board[i] == 0) {                         //If unoccupied
            board[i] = player;                      //Try the move
            int thisScore = -minimax(player*-1);    //calculate the score for the move
            if(thisScore > score) {                 // check if score is lesser than prev
                score = thisScore;                  // minimising the score 
                move = i;                           // replace old i with new updated i if true
            }               
            board[i] = 0;                           //Reset move after trying
        }
    }

    if(move == -1) 
        return 0;
    
    return score;
}

// Function to get the MiniMax computer input (One Player Mode: Hard)
int computerMove(){
    int move = -1;          
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {                    // for all moves
        if(board[i] == 0) {                     // if its unoccupied
            board[i] = 1;                       // try the move 
            int tempScore = -minimax(-1);       // calculate the score for the move
            board[i] = 0;                       // reset the move 
            if(tempScore > score) {             // check if its greater than prev move 
                score = tempScore;              // maximising the score 
                move = i;                       // replace old i with new updated i if true
            }
        }
    }
    //returns a score based on minimax tree at a given node.
    return move;
}