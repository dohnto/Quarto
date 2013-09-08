#ifndef PLAYERMINIMAX_H
#define PLAYERMINIMAX_H

#include "playernovice.h"
#include "QPair"


class PlayerMiniMax : public PlayerNovice
{
public:
    /** constructor */
    PlayerMiniMax(QString name, unsigned depth, Board *board, QObject *parent);
    Piece *choosePiece();

private:
    // TODO - cachovani stromu
    // promenna ukazujici na koren stromu minimax

    unsigned depth;

    QPair<unsigned, unsigned> chooseField(Piece *piece);
    /** Places piece - recursive method generating adversarial search tree.*/
    QPair<int, int> place(Piece *piece, int alpha, int beta, unsigned D);
    /** Chooses piece - recursive method generating adversarial search tree.*/
    QPair<int, int> choose(int alpha, int beta);
};

#endif // PLAYERMINIMAX_H
