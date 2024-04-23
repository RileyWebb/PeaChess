#include "san.h"

char SAN_PieceChar(piece_type type) 
{
    switch (type)
    {
        case PIECE_TYPE_BISHOP: return 'B';
        case PIECE_TYPE_KING: return 'K';
        case PIECE_TYPE_KNIGHT: return 'N';
        case PIECE_TYPE_QUEEN: return 'Q';
        case PIECE_TYPE_ROOK: return 'R';
        //case PIECE_TYPE_PAWN: return 0;
        default: return 0;
    }
}