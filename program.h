#ifndef __PROGRAM_H__
#define __PROGRAM_H__
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

//  determines gamemode
int gamemode();

// deteremines whether it's possible to place a new symbol
bool is_turn_possible(size_t size, int matrix[size][size]);

// determines whether the game is won
int is_game_won(size_t size, int matrix[size][size]);

// determines whether it's possible to win the curent game
bool is_game_winnable(size_t size, int matrix[size][size]);

int minimax(size_t size, int matrix[size][size], int player);

void computer_move(size_t size, int matrix[size][size]);

#endif