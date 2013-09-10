#ifndef PLAYERMINIMAX_H
#define PLAYERMINIMAX_H

#include "playernovice.h"
#include "piece.h"
#include "QPair"


class PlayerMiniMax : public PlayerNovice
{
public:
    /** constructor */
    PlayerMiniMax(QString name, unsigned maxDepth, Board *board, QObject *parent);
    Piece *choosePiece();

private:
    // TODO - cachovani stromu
    // promenna ukazujici na koren stromu minimax

    unsigned maxDepth; /**< max depth */
    QPair<unsigned, unsigned> bestPos;
    Piece *bestPiece;

    QPair<unsigned, unsigned> chooseField(Piece *piece);    
    int alphabeta(Board* board, Piece* piece, unsigned D, int alpha, int beta, bool maximize);
    int evalGameState(Board* board, Piece* piece);
};

#endif // PLAYERMINIMAX_H
