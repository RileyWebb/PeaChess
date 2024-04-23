#include <string.h>

#include "chess.h"
#include "debug.h"

#include "pgn.h"

void PGN_Load(game_t *game, char *src) 
{
    char *next = src;
    while (next = strchr(next, '[') != NULL)
    {
        char *name;
        size_t name_len = strchr(next, ' ') - next + 1;

        if (!name_len)
        {
            DEBUG_ERROR("Unable to read PGN:\n%s", src);
            return 0;
        }

        strncpy(name, next + 1, strchr(next, ' ') - next + 1);

        char *value;
        size_t value_len = strchr(next, "\"") - next + 1;
        /* code */
    }

}