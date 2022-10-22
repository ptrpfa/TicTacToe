//Tic-tac-toe Game
//Two Player Mode

#include <stdio.h>

int checkinput =0;

char gridChar(int i) {

    switch(i) {
        case -1:
            return 'X'; //Plater 1
        case 0:
            return ' '; //Empty
        case 1:
            return 'O'; //Player 2
    }

}

void draw(int b[9]) {

    printf(" %c | %c | %c\n",gridChar(b[0]),gridChar(b[1]),gridChar(b[2]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",gridChar(b[3]),gridChar(b[4]),gridChar(b[5]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",gridChar(b[6]),gridChar(b[7]),gridChar(b[8]));

}

int win(const int board[9]) {
    //determines if a player has won, returns 0 otherwise.
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}}; //Positions to win
    int i;
    for(i = 0; i < 8; ++i) {
        if(board[wins[i][0]] != 0 && //Check if empty, '0' is empty
           board[wins[i][0]] == board[wins[i][1]] && //Check if first of element of the condition above is eql to to second element 
           board[wins[i][0]] == board[wins[i][2]]){ //Check if first element of the condition above is eql to the third element 
            return board[wins[i][2]]; //All condition fufill, return the winner character ('O' or 'X')
        }
    }
    return 0; //Else no one win returns '0'
}

void playerMove(int board[9]) {
    int move = 0;
    int redo = 0;
    do {
        printf("\nPlayer 1 (X) Input move ([0..8]): ");
        scanf("%d", &move);
        if(move >= 9 || move <0){ //If user input is more than 9 or less than 0 (Out of Grid)
            printf("\nMove number out of grid. Try again...\n"); //Indicate Error
            printf("\n");
            draw(board); //Display the board again for player to choose
            redo = 1; //Set to redo, to run through the loop again
        }else if(board[move] != 0){ //Check if board is taken by a character already
            printf("\nTaken Spot, try again!\n"); //Indicate Error
            printf("\n"); 
            draw(board); //Display the board agian for player to choose
            redo = 1; //Set to redo, run through the loop agaain
        }else{
            board[move] = -1; //Set on the Grid 'X' (Player 1)
            redo = 0; //Indicate zero to get out of the loop
        }
        printf("\n");
    } while ( redo == 1);
}

void player2Move(int board[9]){
    int move = 0;
    int redo = 0;
    do{
        printf("\nPlayer 2 (O) Input move ([0..8]): ");
        scanf("%d", &move); //Get the move number
        if(move >= 9 || move <0){ 
            printf("\nMove number out of grid. Try again...\n");
            printf("\n");
            draw(board);
            redo = 1;
        }else if(board[move] != 0){
            printf("\nTaken Spot, try again!\n");
            printf("\n");
            draw(board);
            redo = 1;
        }else{
            board[move] = 1; //Set the move choosen to the grid
            redo = 0;
        }
        printf("\n");
    }while(redo == 1); //Make sure player choose the grid else reloop    
}


int choosemode(){       // choose pvp or player vs ai 
    int user_input = 0;
    int undo = 0;
    do{
        printf("\nPlayer vs Player (1) or Player vs AI (2)\n");
        scanf("%d", &user_input);       //Get the user input 
        if(user_input==1){
               printf("You Have Chosen PVP Mode\n");
               undo = 0;
        }else if(user_input==2){
            printf("You Have Chosen Player vs AI Mode");
            undo = 0;
        }else{
            printf("\nInput number out of range. Try again...\n");
            undo = 1;
        }
    }while(undo == 1); //Make sure player choose within the range    
    return user_input;  // return either 0 or 1 
}



int minimax(int board[9], int player) {
    //How is the position like for player (their turn) on board?
    int winner = win(board);        // getting the output from checkwinner func, '0' for no winner 
    if(winner != 0)                 // checking if theres winner 
    return winner*player;                 // return if theres winner 
    
    int move = -1;
    int score = -2;     //Losing moves are preferred to no move
    int i;
    for(i = 0; i < 9; ++i) {            //For all moves,
        if(board[i] == 0) {         //If unoccupied
            board[i] = player;          //Try the move
            int thisScore = -minimax(board, player*-1);   // calculate the score for the move
            if(thisScore > score) {       // check if score is lesser than prev
                score = thisScore;      // minimising the score 
                move = i;            // replace old i with new updated i if true
            }               
            board[i] = 0;           //Reset move after trying
        }
    }
    if(move == -1) return 0;
    return score;
}

void computerMove(int board[9]) {
    int move = -1;          
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {        // for all moves
        if(board[i] == 0) {         // if its unoccupied
            board[i] = 1;           // try the move 
            int tempScore = -minimax(board, -1);    // calculate the score for the move
            board[i] = 0;           // reset the move 
            if(tempScore > score) {     // check if its greater than prev move 
                score = tempScore;          // maximising the score 
                move = i;                   // replace old i with new updated i if true
            }
        }
    }
    //returns a score based on minimax tree at a given node.
    board[move] = 1;            // AI played the best move 
}

void aiplayerMove(int board[9]) {
int move = 0;
do {
start:
printf("\nInput move ([0..8]): ");      // ask user for input 
scanf("%d", &move);             // ask user for input 
if(board[move] != 0) {          // check if its occupied 
printf("Its Already Occupied !");   
goto start;     // go back and ask user for input again if its occupied
}
printf("\n");
} while (move >= 9 || move < 0 && board[move] == 0);        // keep looping if theres still space
board[move] = -1;           // replace 0 with -1 on board 
}


int gofirstorsecond(){       // choose to go first or second in ai mode
    int reloop = 0;
    while(checkinput == 0){
    do{
                printf("\nComputer: O, You: X\nPlay (1)st or (2)nd?\n");       //ask user who go first
                scanf("%d",&checkinput);        // ask user for input 1 / 2 
                printf("\n");
                if(checkinput == 1 || checkinput == 2){
                    reloop = 0;
                }else{
                printf("\nInput number out of range. Try again...");
                reloop = 1;
                }
    }while(reloop == 1); //Make sure player choose within the range    
    return checkinput;  // return either 1 or 2 which will replace global variable 0 
    }
}



int main() 
{
    int userinput = 0;
    int player=0;
    unsigned turn = 0;  
    int reloop =0; 
    int board[9] = {0,0,0,0,0,0,0,0,0}; // Initialise, the board, 0 is empty string ' '
    userinput = choosemode();
    for(turn = 0; turn < 9 && win(board) == 0; ++turn)  //Loop through 9 turns 
    { 
        if(userinput==1){           // if pvp mode 
                if(player == 0){
            draw(board); //Display the board
            playerMove(board); //Let the player choose
            player = 1; //Change to player 1
                }else {
            draw(board); // Display the board
            player2Move(board); //Let the player choose
            player = 0; //Change to player 0
        }
        }
        else{               // AI mode 
        player = gofirstorsecond();
        if((turn+player) % 2 == 0){ // if even % 2 then com move first 
        computerMove(board);   
                }                   
        else {
        draw(board);                // display tic tac toe board 
        aiplayerMove(board);          // player move first
        draw(board);                // display tic tac toe board to show the final result win or lose or draw 

                }
        }
        
    }

    switch(win(board)) {
        case 0:
            printf("A draw. Better Luck Next Time.\n");
            break;
        case 1:
            draw(board);
            if(userinput==1){
            printf("Player 2 Wins! Awesome!\n");
            }
            else{
            printf("You've lost! Computer Wins! Better Luck Next Time. \n");
            }
            break;
        case -1:
            draw(board);
            if(userinput==2){
            printf("You've Won! Awesome!\n");
            }
            else{
            printf("Player 1 Wins! Awesome!\n");
            }
            break;
    }
}
