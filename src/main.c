#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"

int main(){

    char *data = malloc(1024);
    strcpy(data, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    
    int v = loadBoardFromString(data);

    if(v == 0){
        printf("Error parsing string\n");
    }
    
    printBoard();
    int r = play(0b00010000, 0b00100000);

    if(r == 0){
        printf("Failed to move piece\n");
    }

    return 0;
}