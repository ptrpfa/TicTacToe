//Tic-tac-toe Game
//Two Player Mode

#include <stdio.h>

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

int main() {
    int board[9] = {0,0,0,0,0,0,0,0,0}; // Initialise, the board, 0 is empty string ' '
    int player = 0; // Player 0 starts first
    unsigned turn = 0;  
    printf("\n");
    for(turn = 0; turn < 9 && win(board) == 0; ++turn) { //Loop through whole grid
        if(player == 0){
            draw(board); //Display the board
            playerMove(board); //Let the player choose
            player = 1; //Change to player 0
        }else {
            draw(board); // Display the board
            player2Move(board); //Let the player choose
            player = 0; //Change to player 0
        }
    }
    
    switch(win(board)) {
        case 0:
            printf("A draw. Try Again.\n");
            break;
        case 1:
            draw(board);
            printf("Player 2, You win! Inconceivable!\n");
            break;
        case -1:
            draw(board);
            printf("Player 1, You win! Inconceivable!\n");
            break;
    }
}