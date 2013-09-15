#include "playerminimax.h"
#include "board.h"
#include <QStack>
#include <iostream>
#include <cassert>

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
        struct AlphaBetaResult result = alphabetaX(board, piece, maxDepth, MINUS_INF, PLUS_INF, true);
        bestPos = result.field;
        bestPiece = result.piece;
        std::cout << "alfabeta = " << result.score << std::endl;
        //std::cerr << "Alfabeta = " << alphabeta(board, piece, 1, INIT_ALPHA, INIT_BETA, true) << std::endl;
    }

    return bestPos;
}

struct AlphaBetaResult PlayerMiniMax::alphabetaX(Board *board, Piece *piece, unsigned depth,
                                                                 int alpha, int beta,
                                                                 bool maximize)
{
    struct AlphaBetaResult bestMove;

    if (depth == 0 || board->getStock().isEmpty() || board->checkVictory()) {
        bestMove.score = (maximize ? -1 : 1) * evalGameState(board, piece);
        return bestMove;
    }


    QPair<unsigned, unsigned> possibleField;
    Board *possibleBoard = NULL;
    Piece *possiblePiece = NULL;

    foreach (possibleField, board->getFreeFields()) {
        possibleBoard = new Board(*board);
        possibleBoard->putPiece(possibleField, piece);

        foreach(possiblePiece, possibleBoard->getStock()) {
            possibleBoard->deletePieceFromStock(possiblePiece);

            if (maximize) {
                struct AlphaBetaResult result = alphabetaX(possibleBoard, possiblePiece, depth - 1, alpha, beta, false);
                if (result.score > alpha) {
                    alpha = result.score;
                    bestMove.field = possibleField;
                    bestMove.piece = possiblePiece;
                }

                if (alpha >= beta) {
                    break; // todo
                }
            } else { // minimize
                struct AlphaBetaResult result = alphabetaX(possibleBoard, possiblePiece, depth - 1, alpha, beta, true);

                if (result.score < beta) {
                    beta = result.score;
                    bestMove.field = possibleField;
                    bestMove.piece = possiblePiece;
                }

                if (alpha >= beta) {
                    break;
                }
            }

            possibleBoard->addPieceToStock(possiblePiece);
        }

        delete possibleBoard;


        if (alpha >= beta) {
            break;
        }
    }

    bestMove.score = maximize ? alpha : beta;
    return bestMove;
}

/**
 * Tree generation with alpha beta pruning
 */
/*
int PlayerMiniMax::alphabeta(Board* board, Piece* piece,
                             unsigned D, int alpha, int beta, bool maximize)
{
    if((D > maxDepth) || (board->getStock().isEmpty()) || board->checkVictory()) {
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

                // pruning
                if(alphaNew >= beta) {
                    break;
                }
            }
            // minimizing player
            else {
                betaNew = alphabeta(possibleBoard, possiblePiece, D + 1, alpha, beta, !maximize);



                if (betaNew < beta) {
                    beta = betaNew;
                }

                // pruning
                if (betaNew <= alpha) {
                    break;
                }

            }

            possibleBoard->addPieceToStock(possiblePiece);
        }

        delete possibleBoard;
    }

    return maximize ? alpha : beta;
}*/

int PlayerMiniMax::evalGameState(Board* board, Piece* piece)
{
    if (board->checkVictory()) { // victory
        return INIT_BETA;
    }

    if (board->getStock().size() == 0) {
        QList<QPair<unsigned, unsigned> > freeFields = board->getFreeFields();
        assert(freeFields.size() == 1);
        board->putPiece(freeFields.first(), piece);
        bool victory = board->checkVictory();
        board->deletePiece(freeFields.first());
        if (victory)
            return -INIT_BETA; // victory of enemy
        else
            return 0; // draw

    }

    int score = 0;

//    std::cout << "#########################################################\n";
//    board->printMatrix();
//    board->printStock();
//    std::cout << "piece: " << piece->toString().toStdString() << std::endl;

    // remaining pieces
    score += remainingPiecesScore(board, piece);

    score += tripletScore();

//    std::cout << "score = " << score << std::endl;
//    std::cout << "#########################################################\n";
    return score;
}

int PlayerMiniMax::tripletScore()
{
    return 0;
}

int PlayerMiniMax::remainingPiecesScore(Board *board, Piece *piece)
{
    Board *possibleBoard = new Board(*board);

    possibleBoard->addPieceToStock(piece);
    Piece *chosenPiece;

    unsigned remaining = possibleBoard->getStock().size();

    foreach (chosenPiece, possibleBoard->getStock()) {
        QPair<unsigned, unsigned> possibleField;

        foreach (possibleField, possibleBoard->getFreeFields()) {
            possibleBoard->putPiece(possibleField, chosenPiece);

            bool victory = possibleBoard->checkVictory();

            possibleBoard->deletePiece(possibleField);

            if (victory) {
//              std::cout << "nemuzu hrat s " << chosenPiece->toString().toStdString() << std::endl;
                remaining--;
                break;
            }
        }
    }

    delete possibleBoard;

    // odd : even
//    std::cout << "remaining = " << remaining << std::endl;
    return (remaining % 2) ? (INIT_BETA - remaining) : (INIT_ALPHA + remaining);
}
