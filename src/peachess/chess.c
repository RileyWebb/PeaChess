#include <stdlib.h>

#include "chess.h"
//#include <x86gprintrin.h>

#define SET(b, i) (b |= ((uint64_t)1 << i))
#define GET(b, i) (b & ((uint64_t)1 << i))
#define CLEAR(b, i) (b &= ~((uint64_t)1 << i))

int move_masks_initilised = 0;

game_t *CreateGame() 
{
    game_t *game = calloc(1, sizeof(game_t));

/*
    game->info = {    
        .site = strdup("PeaChess"),
        .event = strdup("PeaChess Battle"),
        .mode = CHESS_MODE_ICS,
        .time = time(NULL),
    };
*/
    if (move_masks_initilised)
    {
        //C_GenerateMoveMasks();
        move_masks_initilised = 1;
    }
}



bitboard_offsets GetPieceOffset(gamestate_t *state, uint_fast8_t index) 
{
    if (GET(state->boards[OFFSET_PAWN], index)) return OFFSET_PAWN;
    if (GET(state->boards[OFFSET_BISHOP], index)) return OFFSET_BISHOP;
    if (GET(state->boards[OFFSET_ROOK], index)) return OFFSET_ROOK;
    if (GET(state->boards[OFFSET_KNIGHT], index)) return OFFSET_KNIGHT;
    if (GET(state->boards[OFFSET_QUEEN], index)) return OFFSET_QUEEN;
    if (GET(state->boards[OFFSET_KING], index)) return OFFSET_KING;
}

bitboard_offsets GetColorOffset(gamestate_t *state, uint_fast8_t index) 
{
    if (GET(state->boards[OFFSET_BLACK], index)) return OFFSET_BLACK;
    if (GET(state->boards[OFFSET_WHITE], index)) return OFFSET_WHITE;
}

piece_type GetPieceType(gamestate_t *state, uint_fast8_t index) 
{
    if (GET(state->boards[OFFSET_PAWN], index)) return PIECE_TYPE_PAWN;
    if (GET(state->boards[OFFSET_BISHOP], index)) return PIECE_TYPE_BISHOP;
    if (GET(state->boards[OFFSET_ROOK], index)) return PIECE_TYPE_ROOK;
    if (GET(state->boards[OFFSET_KNIGHT], index)) return PIECE_TYPE_KNIGHT;
    if (GET(state->boards[OFFSET_QUEEN], index)) return PIECE_TYPE_QUEEN;
    if (GET(state->boards[OFFSET_KING], index)) return PIECE_TYPE_KING;
}

piece_color GetPieceColor(gamestate_t *state, uint_fast8_t index) 
{
    if (GET(state->boards[OFFSET_BLACK], index)) return PIECE_COLOR_BLACK;
    if (GET(state->boards[OFFSET_WHITE], index)) return PIECE_COLOR_WHITE;
}

void MovePiece(gamestate_t *state, uint_fast8_t from, uint_fast8_t to) 
{
    bitboard_offsets from_piece = GetPieceOffset(state, from);
    bitboard_offsets to_piece = GetPieceOffset(state, to);

    bitboard_offsets from_color = GetColorOffset(state, from);
    bitboard_offsets to_color = GetColorOffset(state, to);

    CLEAR(state->boards[GetPieceOffset(state, to)], to);
    SET(state->boards[GetPieceOffset(state, from)], to);
    CLEAR(state->boards[GetPieceOffset(state, from)], from);

    CLEAR(state->boards[OFFSET_OCCUPIED], from);
    SET(state->boards[OFFSET_OCCUPIED], to);

    CLEAR(state->boards[OFFSET_WHITE], to);
    CLEAR(state->boards[OFFSET_BLACK], to);
    SET(state->boards[GetColorOffset(state, from)], to);
    CLEAR(state->boards[OFFSET_WHITE], from);
    CLEAR(state->boards[OFFSET_BLACK], from);
}

uint64_t pawnMoves[BOARDSIZE * BOARDSIZE];
uint64_t pawnAttacks[BOARDSIZE * BOARDSIZE];

//generate attacks (moves for piece & opponents occupied mask)

uint8_t C_ValidPawnMoves(gamestate_t *state, uint_fast8_t index) 
{
    for (size_t i = 0; i < BOARDSIZE * BOARDSIZE; i++)
    {
        //pawnAttacks[i] = 
        /* code */
    }
    
}

uint64_t C_ValidMoves(gamestate_t *state, uint_fast8_t index)
{
    if (!GET(state->boards[OFFSET_OCCUPIED], index))
        return 0;

    switch (GetPieceType(state, index))
    {
        case PIECE_TYPE_PAWN:
            /* code */
            break;
        
        default:
            break;
    }

    
}

void C_GenerateMoves(gamestate_t *state) 
{
    for (size_t i = 0; i < BOARDSIZE * BOARDSIZE; i++)
        state->moves[i] = C_ValidMoves(state, i);    
}