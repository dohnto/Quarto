#include "playerminimax.h"
#include "board.h"
#include <QStack>
#include <iostream>

PlayerMiniMax::PlayerMiniMax(QString name, unsigned maxDepth,
                             Board *board, QObject *parent) :
    PlayerNovice(name, board, parent), maxDepth(maxDepth)
{
    bestPiece = NULL;
    bestPos.first = bestPos.second = 0;
}

Piece* PlayerMiniMax::choosePiece()
{
    return (bestPiece == NULL) ? PlayerNovice::choosePiece() : bestPiece;
}

/**
 * Player generates the minimax tree of the depth D while utilizing
 * alpha-beta pruning.
 */
QPair<unsigned, unsigned> PlayerMiniMax::chooseField(Piece *piece)
{            
    if(board->getStock().size() > (QUARTO_MOVES - NOVICE_MOVES_COUNT)) {
        return PlayerNovice::chooseField(piece);
    }

    // generate search tree
    if(board->getStock().isEmpty()) { /* last free field */
        bestPos = board->getFreeFields().first();
        bestPiece = NULL;
    } else {
        std::cerr << "Alfabeta = " << alphabeta(board, piece, 1, INIT_ALPHA, INIT_BETA, true) << std::endl;
    }

    return bestPos;
}

/**
 * Tree generation with alpha beta pruning
 */
int PlayerMiniMax::alphabeta(Board* board, Piece* piece,
                             unsigned D, int alpha, int beta, bool maximize)
{
    //if((D > maxDepth) || (board->getStock().isEmpty()) || board->checkVictory()) {
    if((D > maxDepth) || (board->getStock().isEmpty())) {
        int boardScore = evalGameState(board, piece);
        return maximize ? -boardScore : boardScore;
    }

    QPair<unsigned, unsigned> possibleField;
    Board *possibleBoard = NULL;
    Piece *possiblePiece = NULL;
    int alphaNew, betaNew;

    foreach(possibleField, board->getFreeFields()) {
        possibleBoard = new Board(*board);
        possibleBoard->putPiece(possibleField, piece);

        foreach(possiblePiece, possibleBoard->getStock()) {
            possibleBoard->deletePieceFromStock(possiblePiece);

            // maximizing player
            if(maximize) {
                alphaNew = alphabeta(possibleBoard, possiblePiece, D + 1, alpha, beta, !maximize);

                if(alphaNew > alpha) {
                    alpha = alphaNew;

                    if(D == 1) {                        
                        bestPiece = possiblePiece;
                        bestPos   = possibleField;
                    }
                }

                std::cout << "alphaNew = " << alphaNew << std::endl;
                std::cout << "beta = " << beta << std::endl;
                std::cout << "alphaNew >= beta : " << (alphaNew >= beta ? "true" : "false") << std::endl;

                bool res = alphaNew >= beta;

                // pruning                
                if(res) {
                    break;
                }
            }
            // minimizing player
            else {
                betaNew = alphabeta(possibleBoard, possiblePiece, D + 1, alpha, beta, maximize);

                if(betaNew < beta) {
                    beta = betaNew;
                }

                // pruning
                if(betaNew <= alpha) {
                    break;
                }
            }

            possibleBoard->addPieceToStock(possiblePiece);
        }

        delete possibleBoard;
    }

    return maximize ? alpha : beta;
}

int PlayerMiniMax::evalGameState(Board* board, Piece* piece)
{
    static int i = 0;
    static int retvals[12] = {8,3,-15,19,38,100,1,0,-90,-12,14,40};

//    if (board->checkVictory()) {
//        //std::cerr << "pes\n";
//        return INIT_BETA;
//    }

    return retvals[i++];
}
