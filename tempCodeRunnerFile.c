
void playGame() {
    char winner = ' ';
    bool playerWon = false;
    bool aiWon = false;

    while (winner == ' '){
        // Tell player which piece they starting with
        printf("Player %c's turn!\n", player);

        // Display the current board
        display_board();

        // Get the player's move
        struct Move player_move = get_player_move();

        // Update the board
        update_board(player, player_move);

        // Check game_state
        winner = check_winner();
        if (winner != ' '){
            // Display the final board and continue
            display_board();
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
        winner = check_winner();
        if (winner != ' '){
            // Display the final board and continue
            display_board();
            break;
        }
    }
    
    if (winner == player){
        printf("Game Over. Winner: Player %c!\n", player);
    }
    else if (aiWon && !playerWon){
        printf("Game Over. Winner: AI %c!\n", ai);
    }
    else {
        printf("Game Over. It's a tie!\n");
    }

}
