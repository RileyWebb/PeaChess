#include <uv.h>

#define SV_CLIENT_TIMEOUT 10000
#define SERVER_PORT 7657

typedef struct sv_client_s 
{
    enum client_type
    {
        SV_CLIENT_TYPE_PLAYER,
        SV_CLIENT_TYPE_SPECTATOR,
    } type;

    unsigned int id;

    uv_tcp_t *tcp;
    uv_timer_t *timer;
} sv_client_t;

typedef struct server_s 
{
    enum server_state
    {
        SV_SERVER_STATE_DEAD = 0,
        SV_SERVER_STATE_ALIVE,
    } state;

    uv_tcp_t *tcp;

    sv_client_t **clients;
    size_t client_count;

    uv_loop_t *loop;
    uv_thread_t *thread;
} server_t;

server_t *SV_Create();

void SV_StartThreaded(server_t *server);
void SV_Start(server_t *server);

void SV_Update(server_t *server);

void SV_Destroy(server_t *server);