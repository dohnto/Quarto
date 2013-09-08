#include "playerminimax.h"
#include "board.h"
#include <QStack>

PlayerMiniMax::PlayerMiniMax(QString name, unsigned depth, Board *board, QObject *parent) :
    PlayerNovice(name, board, parent), depth(depth)
{
}

Piece* PlayerMiniMax::choosePiece()
{
    Piece* piece = NULL;
    return piece;
}

/**
 * Player generates the minimax tree of the depth D while utilizing
 * alpha-beta pruning.
 */
QPair<unsigned, unsigned> PlayerMiniMax::chooseField(Piece *piece)
{
    int alpha = INIT_ALPHA;
    int beta  = INIT_BETA;

    // TODO
    QPair<unsigned, unsigned> pair;
    return pair;
}

QPair<int, int> PlayerMiniMax::place(Piece *piece, int alpha, int beta, unsigned D)
{
    // max tree depth reached
    if(D > depth) {
        // TODO
        // call evaluation function
        // return alpha/beta
    }

    QStack<Board*> boards;
    QPair<unsigned, unsigned> pos;

    // expanding one level of adversarial tree
    foreach(pos, board->getFreeFields()) {
        boards.push(new Board(*board));
        boards.top()->putPiece(pos, piece);
    }

    // TODO
    QPair<int, int> pair;
    return pair;
}


QPair<int, int> PlayerMiniMax::choose(int alpha, int beta)
{
}
