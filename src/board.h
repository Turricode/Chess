#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "data_structs.h"

#define BOARD_SIZE 64


/*
    Each piece is represented by 4 bits the first one represents the color
    and the other 3 the piece types
*/

#define KING 0b001
#define QUEEN 0b010
#define BISHOP 0b011
#define ROOK 0b100
#define KNIGHT 0b101
#define PAWN 0b110
#define RESERVED 0b000

#define BLACK 0b1000
#define WHITE 0b0000

typedef struct BOARD_DATA{
    unsigned char current_player;
    unsigned char castle;
    unsigned char en_passant;
    int halfmove;
    int fullmove;
}BoardData;

typedef struct MOVE{
    unsigned char from;
    unsigned char to;
}Move;

extern unsigned char *board;
extern BoardData bd;

int loadBoardFromString(char *string);
int loadPiece(int x, int y, unsigned char piece, unsigned char color);

void printBoard();
int play(unsigned char from, unsigned char to);


void printMoves(List l);

