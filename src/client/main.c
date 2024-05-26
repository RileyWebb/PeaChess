#include "server/server.h"
#include "debug.h"
#include "ui/ui.h"
//#include "fen.h"

int main( int argc, char **argv) 
{
    uint64_t rook[64];

    for (size_t i = 0; i < 64; i++)
    {
        rook[i] = 
        occupancy &= Rook.blockmask[square];
        /* Calculate the magic move index. */
        int index = (occupancy*Rook.magic[square]) >> (64-Rook.bits[square]);
        /* Return the pre-calculated move board. */
        return Rook.moveboard[square][index];
    }

    D_Init();

    server_t *server = SV_Create();

    SV_StartThreaded(server);

    game_t *game = calloc(1, sizeof(game_t));
    game->state = FEN_LoadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    game->state = FEN_LoadState("rnbq1bnr/p1pp1ppp/8/4P3/2P2N2/2pK4/PP1PpPPP/RkBQ1BNR");
    //FEN_LoadFromString(game, "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ");

    UI_Init();
    UI_Start(game);

    SV_Destroy(server);

    D_LogFlush();
}
