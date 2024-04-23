#include <stdlib.h>

#include "chess.h"

#define SET(b, i) (b |= (1 << i))
#define GET(b, i) (b & (1 << i))
#define CLEAR(b, i) (b &= ~(1 << i))

