#include "program.h"
#include "ui.h"

int gamemode(){
    return gamemode_ui();
}

bool is_turn_possible(size_t size, int matrix[size][size]){
    for(size_t i = 0; i < size; i++){
        for(size_t j = 0; j < size; j++){
            if(matrix[i][j] == 0) return true;
        }
    }
    return false;
}

int is_game_won(size_t size, int matrix[size][size]){
    //determines if a player has won, returns 0 otherwise.
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    for(size_t i = 0; i < 8; ++i) {
        if(matrix[0][wins[i][0]] != 0 &&
           matrix[0][wins[i][0]] == matrix[0][wins[i][1]] &&
           matrix[0][wins[i][0]] == matrix[0][wins[i][2]]) return matrix[0][wins[i][2]];
    }
    return 0;
}

bool is_game_winnable(size_t size, int matrix[size][size]){
    size_t flag = 0;
    int result = 0;
    char horizontal[size+1], vertical[size+1], diagonalA[size+1], diagonalB[size+1];
    for(size_t i = 0; i < size; i++){
        memset(horizontal, 0, (size+1)*sizeof(char));
        memset(vertical, 0, (size+1)*sizeof(char));
        if(flag == 0){
            memset(diagonalA, 0, (size+1)*sizeof(char));
            memset(diagonalB, 0, (size+1)*sizeof(char));
        }
        for(size_t j = 0; j < size; j++){
            if(matrix[i][j] != 0) horizontal[strlen(horizontal)] = gridChar(matrix[i][j]);
            if(matrix[j][i] != 0) vertical[strlen(vertical)] = gridChar(matrix[j][i]);
            if(flag == 0){
                if(matrix[j][j] != 0) diagonalA[strlen(diagonalA)] = gridChar(matrix[j][j]);
                if(matrix[j][size-1-j] != 0) diagonalB[strlen(diagonalB)] = gridChar(matrix[j][size-1-j]);
            }
        }
        flag = 1;
        if(strlen(horizontal) < 2 || strlen(vertical) < 2 || strlen(diagonalA) < 2 || strlen(diagonalB) < 2) return true;
        int h = 0, v = 0, a = 0, b = 0;
        for(size_t idx = 0; idx < size; idx++){
            if(horizontal[0] != horizontal[idx] && horizontal[idx] != 0 && horizontal[0] != 0) h = 1;
            if(vertical[0] != vertical[idx] && vertical[idx] != 0 && vertical[0] != 0) v = 1;
            if(diagonalA[0] != diagonalA[idx] && diagonalA[idx] != 0 && diagonalA[0] != 0) a = 1;
            if(diagonalB[0] != diagonalB[idx] && diagonalB[idx] != 0 && diagonalB[0] != 0) b = 1;
            if((a + b + h + v) == 4) result = 1;
        }       
    }
    return (result == 1) ? false : true;
}

int minimax(size_t size, int matrix[size][size], int player) {
    int winner = is_game_won(size, matrix);
    if(winner != 0) return winner*player;

    int move = -1;  //out of array borders
    int score = -2; //Losing moves are preferred to no move
    for(size_t i = 0; i < size*size; ++i) { //check all available moves
        if(matrix[0][i] == 0) {   //If legal
            matrix[0][i] = player;  //Try the move
            int thisScore = -minimax(size, matrix, player*-1);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }   //Pick the one that's worst for the opponent
            matrix[0][i] = 0; //Reset board after try
        }
    }
    if(move == -1) return 0;
    return score;
}

void computer_move(size_t size, int matrix[size][size]){
    int move = -1;
    int score = -2;
    for(size_t i = 0; i < size*size; ++i) {
        if(matrix[0][i] == 0) {
            matrix[0][i] = 1;
            int tempScore = -minimax(size, matrix, -1);
            matrix[0][i] = 0;
            if(tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    //returns a score based on minimax tree at a given node.
    matrix[0][move] = 1;
}