
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

bool is_taken(int row, int col);

// Controls the players move
struct Move {
    int row;
    int col;
}; 

// Creates the board
char board[4][4] = {
    {'0', '1', '2', '3'},
    {'1', ' ', ' ', ' '},
    {'2', ' ', ' ', ' '},
    {'3', ' ', ' ', ' '}
};

void display_board(){ 
    for (int row = 0; row < 4; row++){
        for (int col = 0; col < 4; col ++){
        printf("%c |", board[row][col]);
        }
    printf("\n");
    }
}

// Get the player's move
struct Move get_player_move(){
    struct Move player_move;
    char line[5]; // Size to hold the null characters
    
    // Prompt the player for input
    printf("Enter your move (row and column, seperated by a space): ");

    // Read a line of input
    fgets(line, sizeof(line), stdin);

    // Check if the input was too long
    if (strchr(line, '\n') == NULL){
        // Input was too long, handle error here
        printf("Input too long. Please enter a valid move: ");
        // Clear the input buffer
        int c;
        while((c = getchar()) != '\n' && c != EOF);
        //Try to read the input again
        fgets(line, sizeof(line), stdin);
    }

    // Parse the input
    while (sscanf(line, "%d %d", &player_move.row, &player_move.col) != 2 || player_move.row < 0 || player_move.row > 3 || player_move.col < 0 || player_move.col > 3 || is_taken(player_move.row, player_move.col)){
        printf("Invalid move.\nPlease enter a valid move: ");
        fgets(line, sizeof(line), stdin);
    }

    return player_move;
}


// Get the AI's move
struct Move get_ai_move(){
    struct Move ai_move;
    // // Get AI's move
    do {
        ai_move.row = rand() % 3 + 1;
        ai_move.col = rand() % 3 + 1;
    } while (is_taken(ai_move.row, ai_move.col));
    return ai_move;
}


// Randomly assign starting piece
char start_piece(){
    int randomNum = rand() % 2;
    char piece = (randomNum == 0) ? 'X' : 'O';
    return piece;
}


// Choose player starting piece
char player = 'X';

// Choose ai starting piece
char ai = 'O';

// Check game state
bool check_winner(void) {
    // Check for a win condition
    for(int i = 1; i <= 3; i++){
        // Check rows
        if (board[i][1] != ' ' && board[i][1] == board[i][2] && board[i][2] == board[i][3]){
            return true;
        }

        // Check columns
        else if (board[1][i] != ' ' && board[1][i] == board[2][i] && board[2][i] == board[3][i]){
            return true;
        }

        // Check diagonal top-left to bottom-right
        else if (board[i][i] != ' ' && board[i][i] == board[i+1][i+1] && board[i+1][i+1] == board[i+2][i+2]){
            return true;
        }

        // Check diagonal top-right to bottom-left
        else if (board[i+2][i] != ' ' && board[i+2][i] == board[i+1][i+1] && board[i+1][i+1] == board[i][i+2]){
            return true;
        }
    }

    return false;
}

bool check_draw(void){
    // Check for a draw condition(board full)
    for(int i = 1; i <= 3; i++){
        for (int j = 1; j <= 3; j++){
            if (board[i][j] == ' '){
                // If there's an empty space, the game is not over
                return false;
            }
        }
    }

    // If the board is full and no one has won, it's a draw
    return true;
}

// Check if square is already taken
bool is_taken(int row, int col){
    return board[row][col] != ' ';
}

// Update the current board
void update_board(char player, struct Move move){
    board[move.row][move.col] = player;
}

// Assign player and AI starting piece
void start(void){
    player = start_piece();
    ai = (player == 'X') ? 'O' : 'X';
}

// Reset the game board
void reset_board(void){
    for (int row = 1; row <= 3; row++){
        for (int col = 1; col <= 3; col++){
            board[row][col] = ' ';
        }
    }
}

// Ask user if they want to play again
int playAgain() {
        // Ask the user if they want to play again
        char response;
        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &response); // Note the 
        getchar(); // Consume the newline character

        // Reset the board if the user wants to play again
        if (response == 'y' || response == 'Y'){
            // reset board and other stuff here
            // Creates the board
            reset_board();
            return 1;
        }

        else {
            // Exit loop ig the user doesn't want to play again
            return 0;
        }
}

void playGame() {
    bool tie = false;
    bool playerWon = false;
    bool aiWon = false;

    while (!check_winner() && !check_draw()){
        // Tell player which piece they starting with
        printf("Player %c's turn!\n", player);

        // Display the current board
        display_board();

        // Get the player's move
        struct Move player_move = get_player_move();

        // Update the board
        update_board(player, player_move);

        // Check game_state
        if (check_winner()){
            playerWon = true;
            break;
        }
        if (check_draw()){
            tie = true;
            break;
        }

        // Get the AI's move
        struct Move ai_move = get_ai_move();

        // Check if the square is already taken
        if (is_taken(ai_move.row, ai_move.col)){
            continue;
        }

        // Update the board with the AI's move 
        update_board(ai, ai_move);

        // Check game_state
        if (check_winner()){
            aiWon = true;
            break;
        }
        if (check_draw()){
            tie = true;
            break;
        }
    }
    
    if (playerWon) {
        printf("Game Over. Winner: Player %c!\n", player);
        playerWon = true;
    }
    else if (aiWon) {
        printf("Game Over. Winner: AI %c!\n", ai);
        aiWon = true;
    }
    else if (tie) {
        printf("Game Over. It's a tie!\n");
    }
}


int main(void) {
    // Seed random number generator with the current time
    srand(time(NULL));

    // Initialize play variable
    int play = 1;
        
    do {  
        // Assign player and AI starting pieces
        start();

        // Game loop
        playGame();
        
        // Display the final board
        display_board();

        // Asks user if they want to play again
        play = playAgain();

    } while(play); 
    return EXIT_SUCCESS;
}

