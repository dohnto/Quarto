#ifndef COMMON_H
#define COMMON_H

#include <QString>

const unsigned  PIECE_COUNT     = 16;
const unsigned  MATRIX_SIZE     = 4;
const unsigned  PLAYER_COUNT    = 2;
const int       INIT_ALPHA      = 1024;
const int       INIT_BETA       = -1024;

enum player_e {
    RANDOM,
    NOVICE,
    MINIMAX,
    REMOTE,
    HUMAN
};

struct player_t {
    player_e type;
    unsigned minimax_level;
    QString additional;
};

#endif // COMMON_H
