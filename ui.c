#include "ui.h"

void start_curses(){
    initscr();
	noecho();
	cbreak();
	start_color();
	curs_set(0);
	keypad(stdscr, TRUE);
    clear();
}

void end_curses(){
    getch();
	endwin();
}

int gamemode_ui(){
    //  initialize colors
    init_color(COLOR_WHITE, 1000, 1000, 1000);
    init_color(COLOR_BLACK, 0, 0, 0);
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);

    char* line = "+----------------------------------------+\n";
    char* entryMsg = "    Welcome to the game ""Cross vs Zero""!   ";

    //  welcome message
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(LINES/3-3, (COLS/2-strlen(entryMsg)/2), "%s", line);
    attron(COLOR_PAIR(2) | A_BLINK);
    mvprintw(LINES/3-2, (COLS/2-strlen(entryMsg)/2), "%s", entryMsg);
    attroff(A_BLINK);
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(LINES/3-2, (COLS/2-strlen(entryMsg)/2)+strlen(entryMsg), "%s", "|");
    mvprintw(LINES/3-2, (COLS/2-strlen(entryMsg)/2), "%s", "|");
    mvprintw(LINES/3-1, (COLS/2-strlen(entryMsg)/2), "%s", line);

    // choose within singe- or multi- player mode
    char* single = " Singleplayer ";
    char* multi = " Multiplayer ";

    int but = 0, flag = 0;
    while(but != '\n'){
        if(flag == 0){
            attron(COLOR_PAIR(3));
            mvprintw(LINES/3+2, (COLS/2-strlen(single)/2)+1, "%s", single);
            attron(COLOR_PAIR(2));
            mvprintw(LINES/3+4, (COLS/2-strlen(single)/2)+1, "%s", multi);
        }else if(flag == 1){
            attron(COLOR_PAIR(2));
            mvprintw(LINES/3+2, (COLS/2-strlen(single)/2)+1, "%s", single);
            attron(COLOR_PAIR(3));
            mvprintw(LINES/3+4, (COLS/2-strlen(single)/2)+1, "%s", multi);
        }
        but = getch();
        if(but == KEY_UP && flag == 1) flag = 0;
        if(but == KEY_DOWN && flag == 0) flag = 1;
    }
    return flag;
}

char gridChar(int i) {
    switch(i) {
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }
    return ' ';
}

void render(size_t size, int matrix[size][size], size_t T_score, size_t X_score, size_t O_score){
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_CYAN, 229, 204, 255);
    init_color(COLOR_WHITE, 1000, 1000, 1000);
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_CYAN, COLOR_CYAN);

    clear();

    int x_start = (COLS - 17) / 2;
    int y_start = 3;
    attrset(COLOR_PAIR(1) | A_BOLD | A_STANDOUT);

    for (int y = y_start; y < y_start + 13; y++){
        for (int x = x_start; x < x_start + 19; x++){
            mvprintw(y, x, " ");
        }
    }
    y_start = 3;
    for (int y = 0; y < size; y++){
        for (int x = 0; x < size; x++) {
            attron(COLOR_PAIR(2));
            mvprintw(18, COLS/2-2, "TIE: %zu", T_score);
            mvprintw(6, COLS/3-5, "X: %zu", X_score);
            mvprintw(6, 2*COLS/3+3, "O: %zu", O_score);
            if(matrix[y][x] == -1) attrset(COLOR_PAIR(2) | A_BOLD | A_PROTECT);
            else if(matrix[y][x] == 1) attrset(COLOR_PAIR(3) | A_BOLD | A_PROTECT);
            else if(matrix[y][x] == 0) attrset(COLOR_PAIR(4) | A_BOLD | A_PROTECT);
            mvprintw(y_start + (y * size) + 1, x_start + (x * 6) + 1, "     ");
            mvprintw(y_start + (y * size) + 2, x_start + (x * 6) + 1, "  %c  ", gridChar(matrix[y][x]));
            mvprintw(y_start + (y * size) + 3, x_start + (x * 6) + 1, "     ");
        }
        y_start++;
    }
}

void pl_move(size_t size, int matrix[size][size], int player, size_t T_score, size_t X_score, size_t O_score){
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_CYAN, 229, 204, 255);
    init_color(COLOR_WHITE, 1000, 1000, 1000);
    init_color(COLOR_YELLOW, 1000, 1000, 600);
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_CYAN, COLOR_CYAN);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);

    clear();

    int x_start = (COLS - 17) / 2;
    int y_start = 3;
    attrset(COLOR_PAIR(1) | A_BOLD | A_STANDOUT);

    for (int y = y_start; y < y_start + 13; y++){
        for (int x = x_start; x < x_start + 19; x++){
            mvprintw(y, x, " ");
        }
    }
    int c = '$';
    unsigned cell = 4;
    char selected = '@';
    while(c != '\n'){
A:        ;
        y_start = 3;
        int buf = matrix[0][cell];
        matrix[0][cell] = selected;
        for (int y = 0; y < size; y++){
            for (int x = 0; x < size; x++) {
                attron(COLOR_PAIR(2));
                mvprintw(18, COLS/2-2, "TIE: %zu", T_score);
                mvprintw(6, COLS/3-5, "X: %zu", X_score);
                mvprintw(6, 2*COLS/3+3, "O: %zu", O_score);
                if(matrix[y][x] == -1) attrset(COLOR_PAIR(2) | A_BOLD | A_PROTECT);
                else if(matrix[y][x] == 1) attrset(COLOR_PAIR(3) | A_BOLD | A_PROTECT);
                else if(matrix[y][x] == 0) attrset(COLOR_PAIR(4) | A_BOLD | A_PROTECT);
                if(matrix[y][x] != selected){
                    mvprintw(y_start + (y * size) + 1, x_start + (x * 6) + 1, "     ");
                    mvprintw(y_start + (y * size) + 2, x_start + (x * 6) + 1, "  %c  ", gridChar(matrix[y][x]));
                    mvprintw(y_start + (y * size) + 3, x_start + (x * 6) + 1, "     ");
                } else {
                    attrset(COLOR_PAIR(5) | A_BOLD | A_PROTECT);
                    mvprintw(y_start + (y * size) + 1, x_start + (x * 6) + 1, "     ");
                    mvprintw(y_start + (y * size) + 2, x_start + (x * 6) + 1, "  %c  ", gridChar(buf));
                    mvprintw(y_start + (y * size) + 3, x_start + (x * 6) + 1, "     ");
                    matrix[0][cell] = buf;
                }
            }
            y_start++;
        }
        c = getch();
        switch(c){
            case KEY_DOWN:
                if(cell <= 5) cell += 3;
                break;
            case KEY_UP:
                if(cell >= 3) cell -= 3;
                break;
            case KEY_LEFT:
                if(cell != 0) cell--;
                break;
            case KEY_RIGHT:
                if(cell != 8) cell++;
                break;
            default: ;
        }
        refresh();
    }
    if(matrix[0][cell] == 0) matrix[0][cell] = player;
    else goto A;
}

