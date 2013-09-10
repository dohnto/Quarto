#include "playerminimax.h"
#include "board.h"
#include <QStack>

PlayerMiniMax::PlayerMiniMax(QString name, unsigned depth, Board *board, QObject *parent) :
    PlayerNovice(name, board, parent), maxDepth(maxDepth)
{
    bestPiece = NULL;
    bestPos.first = bestPos.second = 0;
}

Piece* PlayerMiniMax::choosePiece()
{
    return (bestPiece == NULL) ? PlayerRandom::choosePiece() : bestPiece;
}

/**
 * Player generates the minimax tree of the depth D while utilizing
 * alpha-beta pruning.
 */
QPair<unsigned, unsigned> PlayerMiniMax::chooseField(Piece *piece)
{
    // generate search tree
    alphabeta(board, piece, 1, INIT_ALPHA, INIT_BETA, true);

    return bestPos;
}

/**
 * Tree generation with alpha beta pruning
 */
int PlayerMiniMax::alphabeta(Board* board, Piece* piece, unsigned D, int alpha, int beta, bool maximize)
{
    if(D > maxDepth) {
        return evalGameState(board, piece);
    }

    QPair<unsigned, unsigned> possibleField;
    Board *possibleBoard = NULL;
    Piece *possiblePiece = NULL;
    int alphaNew, betaNew;

    foreach(possibleField, board->getFreeFields()) {
        possibleBoard = new Board(*board);
        possibleBoard->putPiece(possibleField, piece);

        foreach(possiblePiece, possibleBoard->getStock()) {
            // maximizing player
            if(maximize) {
                alphaNew = alphabeta(possibleBoard, possiblePiece, D + 1, alpha, beta, !maximize);

                // pruning
                if(alphaNew >= beta) {
                    break;
                }

                if(alphaNew > alpha) {
                    alpha = alphaNew;

                    if(D == 1) {
                        bestPiece = possiblePiece;
                        bestPos   = possibleField;
                    }
                }
            }
            // minimizing player
            else {
                betaNew = alphabeta(possibleBoard, possiblePiece, D + 1, alpha, beta, maximize);

                // pruning
                if(betaNew <= alpha) {
                    break;
                }

                if(betaNew < beta) {
                    beta = betaNew;
                }
            }
        }
    }

    return maximize ? alpha : beta;
}

int PlayerMiniMax::evalGameState(Board* board, Piece* piece)
{
    // TODO - implement! :-D

    return rand() % (2 * INIT_ALPHA + 1) - INIT_ALPHA;
}
