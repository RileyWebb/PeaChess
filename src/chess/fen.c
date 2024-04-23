#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "debug.h"
//#include "chess.h"

//#include "fen.h"

/*
void FEN_LoadFromString(game_t *game, char *str) 
{
    if (!game)
        game = calloc(1, sizeof(game_t));

    board_t *board = &game->board;

    memset(board, 0, sizeof(board_t));

    int i = 0;
    int x = 0;
    int y = 7;

    char *cur = str;

    while(*cur)
    {
        if (y <= 0 || x > CHESS_BOARDSIZE)
        {
            //DEBUG_ERROR("Invalid FEN String");
            //return 0;
        }

        if (*cur == '/')
        {
            y--;
            x = 0;
            cur++;
        }

        piece_t *piece = &game->board.pieces[x][y];

        piece_color color = isupper(*cur) ? PIECE_COLOR_WHITE : PIECE_COLOR_BLACK;

        switch (tolower(*cur))
        {
            case 'r':
                *piece = PieceCreate(PIECE_TYPE_ROOK, color); 
                 break;
            case 'n':
                *piece = PieceCreate(PIECE_TYPE_KNIGHT, color); 
                break;
            case 'b':
                *piece = PieceCreate(PIECE_TYPE_BISHOP, color); 
                break;
            case 'q':
                *piece = PieceCreate(PIECE_TYPE_QUEEN, color); 
                break;
            case 'k':
                *piece = PieceCreate(PIECE_TYPE_KING, color); 
                break;
            case 'p':
                *piece = PieceCreate(PIECE_TYPE_PAWN, color); 
                break;
            default:
                if (isdigit(*cur))
                    x += atoi(cur);
                break;
        }

        if (*piece)
            x++;

        cur++;
    } 

    GenerateValidMoves(game);
}
*/