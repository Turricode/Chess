#include "board.h"

unsigned char *board; // 'Universal' board
BoardData bd;  // 'Universal' struct that holds data about the game state

const char piece_vals_white[7] = {'k', 'q', 'b', 'r', 'n', 'p'};
const char piece_vals_black[7] = {'K', 'Q', 'B', 'R', 'N', 'P'};


void printMoves(List l){
    List cpy = l;
    if(l == NULL){
        printf("Empty move list\n");
    }
    while(!isListEmpty(cpy)){
        Move m = *(Move*)(cpy->data);
        printf("From: %d | To: %d\n", m.from, m.to);
        cpy = cpy->next;
    }

}

//Auxiliary funtion
int findByIndex(const char *arr, char c){
    for(int i = 0; i < 7; i++){
        if (arr[i] == c)
            return i;
    }
    return -1;
}

//Essentially clear board
void initBoard(){
    board = malloc(BOARD_SIZE);

    for(int i = 0; i < BOARD_SIZE; i++){
        board[i] = 0b0;
    }
}

//Loads a piece into the board
int loadPiece(int x, int y, unsigned char piece, unsigned char color){
    if(x > 8 && x < 0 && y > 8 && y < 0 && board[y * 8 + x] != 0b0)
        return 0;
    board[y * 8 + x] = piece | color;
    return 1;
    
}

//Parse the first part of the FEN string
int parseBoard(char *string){

    int line = 0;
    int column = 0;

    for(int i = 0; i < strlen(string); i++){

        if(string[i] > 47 && string[i] < 57)
            column += (int)(string[i] - 47);

        if(string[i] > 64 && string[i] < 91){
            int v = findByIndex(piece_vals_black, string[i]);

            if(v == -1)
                return 0;
            
            board[line * 8 + column] = (v + 1) | BLACK; 
            column++;
        }

        if(string[i] > 96 && string[i] < 123){
            int v = findByIndex(piece_vals_white, string[i]);

            if(v == -1)
                return 0;

            board[line * 8 + column] = (v + 1) | WHITE;
            column++;
        }

        if(string[i] == '/'){
            column = 0;
            line ++;
        }

    }
}

//Parses the player part of FEN
int parsePlayer(char *string){
    if(!strcmp("w", string))
        bd.current_player = WHITE;
    else
        bd.current_player = BLACK;
}

//Parses the available castles of FEN
int parseCastle(char *string){
    bd.castle = 0b0;

    for(int i = 0; i < strlen(string); i++){
        switch (string[i])
        {
        case 'K':
            bd.castle += 0b1000;
            break;
        
        case 'Q':
            bd.castle += 0b0100;
            break;

        case 'k':
            bd.castle += 0b0010;
            break;
        
        case 'q':
            bd.castle += 0b0001;
            break;
        
        default:
            break;
        
        }
    }

    return 1;
}

//Parses the en passant of FEN
int parseEnPassant(char *string){

    if(!strcmp("-", string))
        return 1;
    
    char column = (string[0] - 97) << 4;
    char line = string[1] - 49;

    bd.en_passant = column | line;

    return 1;
}

//Puts all of the parsing funtions together to fully parse FEN string into bd.
//Also its a public funtion
int loadBoardFromString(char *string){
    initBoard();

    char *brd = strtok(string, " ");
    char *player = strtok(NULL, " ");
    char *can_castle = strtok(NULL, " ");
    char *en_passant = strtok(NULL, " ");
    char *halfmoves = strtok(NULL, " ");
    char *fullmoves = strtok(NULL, " ");

    parseBoard(brd);
    parsePlayer(player);
    parseCastle(can_castle);
    parseEnPassant(en_passant);

    bd.halfmove = atoi(halfmoves);
    bd.fullmove = atoi(fullmoves);

    return 1;

}

//Simple funtion mostly used for debbuging I guess. It allows to get a 
//ASCII view of the board
void printBoard(){
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            unsigned char value = board[y * 8 + x];
            if(value == RESERVED){
                if((y * 8 + x + (y % 2)) % 2 == 0)
                    printf("| # ");
                else
                    printf("| & ");
            }else if(value >> 3 == 0b1){
                printf("| %c ", piece_vals_black[value - 0b1001]);
            }else{
                printf("| %c ", piece_vals_white[value - 1]);
            }
                   
        }
        printf("\n");
    }
}

//Play funttion needs a lot of work, so far it only validates if
//the piece you want to move is valid.

//TODO make a rule system for each piece

List pawn_moves(int from_col, int from_line){
    List final = createList();
    
    if(board[(from_line + 1) * 8 + from_col] == RESERVED){
        Move *data = malloc(sizeof(Move));
        data->from = (unsigned char)from_line << 4 | (unsigned char)from_col;
        data->to = (unsigned char)(from_line + 1) << 4 | (unsigned char)from_col;
        final = appendHead(final, data);
    }

    return final;
}

int play(unsigned char from, unsigned char to){
    unsigned char from_line = from >> 4;
    unsigned char from_column = from & 0b00001111;

    Move m = {.from = from, .to = to};

    unsigned char from_piece = board[from_line * 8 + from_column];

    if(from_piece == RESERVED){
        return 0;
    }
    
    if(from_piece >> 3 != bd.current_player){
        return 0;
    }
    switch (from_piece & 0b111)
    {
    case PAWN: ;
        List possible_moves = pawn_moves(from & 0b00001111, from >> 4);

        if(isDataIn(possible_moves, &m, sizeof(Move)))
            return 1;

        return 0;
        break;
    
    default: 
        break;
    }
    return 0;
}