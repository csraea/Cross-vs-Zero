#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

//  starts ncurses
void start_curses();

//  ends curses
void end_curses();

//  grafical interface for choosing gamemode
int gamemode_ui();

//  renders matrix
void pl_move(size_t size, int matrix[size][size], int player, size_t T_score, size_t X_score, size_t O_score);

void render(size_t size, int matrix[size][size], size_t T_score, size_t X_score, size_t O_score);

char gridChar(int i);