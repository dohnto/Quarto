#ifndef COMMON_H
#define COMMON_H

const unsigned PIECE_COUNT = 16;
const unsigned MATRIX_SIZE = 4;
const unsigned PLAYER_COUNT = 2;

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
};

#endif // COMMON_H
