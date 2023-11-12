// Check game state
bool is_game_over(void) {
    bool win = false;

    // Check for a win condition
    for(int i = 1; i <= 3; i++){
        // Check rows
        if (board[i][1] == board[i][2] && board[i][2] == board[i][3]){
            win = true;
            break;
        }

        // Check columns
        else if (board[1][i] == board[2][i] && board[2][i] == board[3][i]){
            win = true;
            break;
        }

        // Check diagonal top-left to bottom-right
        else if (board[i][i] != ' ' && board[i][i] == board[i+1][i+1] && board[i+1][i+1] == board[i+2][i+2]){
            win = true;
            break;
        }

        // Check diagonal top-right to bottom-left
        else if (board[i+2][i] != ' ' && board[i+2][i] == board[i+1][i+1] && board[i+1][i+1] == board[i][i+2]){
            win = true;
            break;
        }
    }
    // Check for a draw condition(board full)
    for(int i = 1; i < 3; i++){
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
