#ifndef _CHESS_H
#define _CHESS_H

#include <stdint.h>
#include <time.h>

#define BOARDSIZE 8

enum {
    A8, B8, C8, D8, E8, F8, G8, H8,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A1, B1, C1, D1, E1, F1, G1, H1
};

static const uint64_t enPassantMask = 0xFF0000FF0000;

typedef enum piece_type
{
    PIECE_TYPE_NONE     = 0,
    PIECE_TYPE_PAWN     = 1,
    PIECE_TYPE_BISHOP   = 2,
    PIECE_TYPE_ROOK     = 3,
    PIECE_TYPE_KNIGHT   = 4,
    PIECE_TYPE_KING     = 5,
    PIECE_TYPE_QUEEN    = 6,
} piece_type;

typedef enum 
{
    OFFSET_WHITE = 0,
    OFFSET_BLACK = 1,
    
    OFFSET_BISHOP = 2,
    OFFSET_KING = 3,
    OFFSET_KNIGHT = 4,
    OFFSET_PAWN = 5,
    OFFSET_QUEEN = 6,
    OFFSET_ROOK = 7,
} bitboard_offsets;

typedef struct position_s 
{
    uint8_t column;
    uint8_t row;
} position_t;

typedef uint8_t piece_t;
typedef uint64_t valid_moves_t;

typedef struct move_s 
{
    position_t from;
    position_t to;
    uint8_t flags;
} move_t;

typedef struct board_s 
{
    uint16_t flags;

    uint64_t pieces[6 * 2];
} board_t;

typedef struct player_s
{
    
} player_t;

typedef struct game_s 
{
    char *event;
    char *site;
    time_t time;
    int round;

    enum 
    {
        CHESS_TERMINATION_UNTERMINATED = 0,
        CHESS_TERMINATION_ABANDONED,
        CHESS_TERMINATION_ADJUDICATION,
        CHESS_TERMINATION_DEATH,
        CHESS_TERMINATION_EMERGENCY,
        CHESS_TERMINATION_NORMAL,
        CHESS_TERMINATION_INFRACTION,
        CHESS_TERMINATION_TIME,
    } termination;

    enum
    {
        CHESS_MODE_UNKNOWN = 0,
        CHESS_MODE_ICS,
        CHESS_MODE_OTB,
    } mode;

    //result
    
    player_t white;
    player_t black;

    board_t board;
    valid_moves_t valid[CHESS_BOARDSIZE][CHESS_BOARDSIZE];

    move_t *moves;
    size_t move_count;
} game_t;

#endif