#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "debug.h"

#include "chess.h"

gamestate_t FEN_LoadState(char *str)
{
	gamestate_t state = {0};

	int i = 0;

	char *cur = str;

	while (*cur && i < BOARDSIZE * BOARDSIZE) {
		if (*cur == ' ')
			break;

		if (isdigit(*cur))
			i += atoi(cur);

		if (isalpha(*cur)) {
			switch (tolower(*cur)) 
            {
			case 'b':
                state.boards[OFFSET_BISHOP] |= ((uint64_t)1 << i);
				break;
			case 'k':
                state.boards[OFFSET_KING] |= ((uint64_t)1 << i);
				break;
			case 'n':
                state.boards[OFFSET_KNIGHT] |= ((uint64_t)1 << i);
				break;
			case 'p':
                state.boards[OFFSET_PAWN] |= ((uint64_t)1 << i);
				break;
            case 'q':
                state.boards[OFFSET_QUEEN] |= ((uint64_t)1 << i);
				break;
			case 'r':
                state.boards[OFFSET_ROOK] |= ((uint64_t)1 << i);
				break;

			default:
				DEBUG_ERROR("Unable to parse FEN (Piece %c is unknown): %s",
							str, *cur);
				return (gamestate_t){0};
			}

            state.boards[OFFSET_OCCUPIED] |= ((uint64_t)1 << i);

			if (isupper(*cur))
                state.boards[OFFSET_WHITE] |= ((uint64_t)1 << i);
            else
                state.boards[OFFSET_BLACK] |= ((uint64_t)1 << i);
            
            i++;
		}

		cur++;
	}

	if (i != BOARDSIZE * BOARDSIZE)
		DEBUG_ERROR("Unable to parse FEN: %s", str);

    return state;
	// GenerateValidMoves(game);
}