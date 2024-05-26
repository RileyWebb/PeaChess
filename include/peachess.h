#include <stdint.h>
#include <time.h>

typedef struct c_state_s {} c_state_t;

typedef struct c_gameinfo_s 
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
} c_gameinfo_t;

typedef struct c_game_s 
{
    //player_t white;
    //player_t black;

    c_gameinfo_t info;

    c_state_t state;

    //move_t *moves;
    size_t move_count;
} c_game_t;

//extern uint64_t c_move_table[Piece][attackByte][defendByte]