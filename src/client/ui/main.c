#include "server/server.h"
#include "debug.h"
#include "client/ui.h"
//#include "fen.h"

int main(int argc, char *argv[]) 
{
    D_Init();

    server_t *server = SV_Create();

    SV_StartThreaded(server);

    game_t *game = calloc(1, sizeof(game_t));
    //FEN_LoadFromString(game, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    //FEN_LoadFromString(game, "rnbqkbnr/pp1ppppR/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2");
    //FEN_LoadFromString(game, "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ");

    UI_Init();
    UI_Start(game);

    uv_sleep(1000);
    SV_Destroy(server);

    D_LogFlush();
}
