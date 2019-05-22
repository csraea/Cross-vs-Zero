#include "program.h"
#include "ui.h"

const static int huPlayer = -1;
const static int aiPlayer = 1;

int main(void){
    start_curses();
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_CYAN, 0, 1000, 1000);
    init_pair(9, COLOR_CYAN, COLOR_BLACK);
    int choise = gamemode_ui();

    size_t X_score = 0;
    size_t O_score = 0;
    size_t T_score = 0;

    int but = 0, result = 0;
    while(but != KEY_F(1)){
        int matrix[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
        while(1){
            pl_move(3, matrix, huPlayer, T_score, X_score, O_score);
            if(is_turn_possible(3, matrix) == true){
                if(choise == 0) computer_move(3, matrix);
                else if(is_game_won(3, matrix) == false) pl_move(3, matrix, aiPlayer, T_score, X_score, O_score);
                render(3, matrix, T_score, X_score, O_score);
            } else {
                render(3, matrix, T_score, X_score, O_score);
                break;
            } 
            result = is_game_won(3, matrix);
            
            if(is_game_winnable(3, matrix) == false && result == 0){
                attrset(COLOR_PAIR(9) | A_BOLD | A_BLINK);
                mvprintw(1, COLS/2-1, "TIE!");
                break;
            } else if(is_game_winnable(3, matrix) == true && result == 1){
                attrset(COLOR_PAIR(9) | A_BOLD | A_BLINK);
                mvprintw(1, COLS/2-3, "O wins!");
                break;
            } else if(is_game_winnable(3, matrix) == true && result == -1){
                attrset(COLOR_PAIR(9) | A_BOLD | A_BLINK);
                mvprintw(1, COLS/2-3, "X wins!");
                break;
            }
        }
        switch(result){
            case 0:
                T_score++;
                break;
            case 1:
                O_score++;
                break;
            case -1:
                X_score++;
                break;
        }
        but = getch();
    }
    end_curses();
}