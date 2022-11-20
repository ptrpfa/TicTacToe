#include <gtk/gtk.h>                // Include GTK library for GUI
#include "../header/config.h"       // Include configuration file

//Global variable
GtkWidget *scoreGrid;
GtkWidget *scoreX, *scoreO, *scoreTie;
/**
 * score[0][0] - score[0][2]: Player vs Player
 * score[1][0] - score[1][2]: Player vs Computer
*/
int score[2][3];   

void Scoreboard(){
    //Create the scoreboard
    scoreGrid = gtk_grid_new (); 
    gtk_widget_set_halign (scoreGrid, GTK_ALIGN_CENTER); 
    gtk_widget_set_valign (scoreGrid, GTK_ALIGN_CENTER);
    gtk_grid_set_column_homogeneous(GTK_GRID(scoreGrid),TRUE); 
    gtk_grid_set_row_homogeneous(GTK_GRID(scoreGrid),TRUE); 
    gtk_grid_set_column_spacing(GTK_GRID (scoreGrid), 50);                      //Set each widget spacing
    CreateCSS(scoreGrid, "scoreGrid");

    scoreX = gtk_label_new(NULL);                                               //Player X Label
    gtk_label_set_markup(GTK_LABEL(scoreX), 
                        "<span>Player X\n</span><span>0</span>");
    gtk_label_set_justify(GTK_LABEL(scoreX), GTK_JUSTIFY_CENTER);  

    scoreTie = gtk_label_new(NULL);                                             //Tie Label
    gtk_label_set_markup(GTK_LABEL(scoreTie), 
                        "<span>Ties\n</span><span>0</span>");
    gtk_label_set_justify(GTK_LABEL(scoreTie), GTK_JUSTIFY_CENTER);  

    scoreO = gtk_label_new(NULL);                                               //Player O Label
    gtk_label_set_markup(GTK_LABEL(scoreO), 
                        "<span>Player O\n</span><span>0</span>");
    gtk_label_set_justify(GTK_LABEL(scoreO), GTK_JUSTIFY_CENTER);          

    CreateCSS(scoreX, "scoreX");
    CreateCSS(scoreTie, "scoreTie");
    CreateCSS(scoreO, "scoreO");
    gtk_grid_attach (GTK_GRID (scoreGrid), scoreX, 0, 0, 3, 2);            //Set to Grid
    gtk_grid_attach (GTK_GRID (scoreGrid), scoreTie, 3, 0, 3, 2);            //Set to Grid
    gtk_grid_attach (GTK_GRID (scoreGrid), scoreO, 6, 0, 3, 2);            //Set to Grid
}

void SetScore(int result){
    /***** Board Status *********/
    //  0:  Game in progress    //
    //  -1: Player 1 Wins       //
    //  1:  Player 2 Wins       //
    //  2:  Game Draw           //
    /****************************/
    char *str;
    if(gameModeOption == 1){            //2-Player mode
        switch(result){
            case -1:                    //Player 1 Wins
                score[0][0] += 1;
                break;
            case 1:                     //Player 2 Wins
                score[0][2] += 1;
                break; 
            case 2:                     //Draw
                score[0][1] += 1;
                break;        
        }        
        str = g_strdup_printf ("<span>Player X\n</span><span>%d</span>", (score[0][0]));
        gtk_label_set_markup (GTK_LABEL(scoreX), str);
        
        str = g_strdup_printf ("<span>Player O\n</span><span>%d</span>", (score[0][2]));   
        gtk_label_set_markup (GTK_LABEL(scoreO), str);    

        str = g_strdup_printf ("<span>Ties\n</span><span>%d</span>", (score[0][1]));
        gtk_label_set_markup (GTK_LABEL(scoreTie), str);
        g_free (str); 

    }else{                              //Ai Mode
        switch(result){
            case -1:                    //Player 1 Wins
                score[1][0] += 1;
                break;
            case 1:                     //Ai Wins
                score[1][2] += 1;
                break; 
            case 2:                     //Draw
                score[1][1] += 1;
                break;        
        }
        str = g_strdup_printf ("<span>Player X\n</span><span>%d</span>", (score[1][0]));
        gtk_label_set_markup (GTK_LABEL(scoreX), str);
        
        str = g_strdup_printf ("<span>Machine O\n</span><span>%d</span>", (score[1][2]));   
        gtk_label_set_markup (GTK_LABEL(scoreO), str);    

        str = g_strdup_printf ("<span>Ties\n</span><span>%d</span>", (score[1][1]));
        gtk_label_set_markup (GTK_LABEL(scoreTie), str);
        g_free (str); 
    }
}