#include <QDebug>
#include "game.h"

/**
 * Constructor
 *
 * @param parent a pointer to the parent
 */
Game::Game(QObject *parent) : QObject(parent)
{
    // Get the instance of the main application
    app = QCoreApplication::instance();

    // create essential objects
    player1 = new PlayerRandom(board, this);
    player2 = new PlayerRandom(board, this);

    turn = player2;

    board   = new Board(this);
    //piece   = new Piece(this);
}

/**
 * Main game function. Creates the objects of Player, Board, Piece.
 * Controls the game state.
 */
void Game::run() {
    qDebug() << "Game is running";                  // TODO delete

    Piece* piece = turn->choosePiece();
    for (unsigned i = 0; i < 3; i++) {                                  // TODO change
        qDebug() << "---------------------";
        turn = getOpponent(turn);
        piece = turn->move(piece);
        // check situation                          // TODO
    }

    quit();
}

/**
 * Quits the application
 */
void Game::quit() {
    emit finished();
}


/**
 * @brief Game::getOpponent
 * @param player
 * @return returns opponent (second player) of given player
 */
Player *Game::getOpponent(Player *player)
{
    if (player == player1)
        return player2;
    if (player == player2)
        return player1;
    else
        throw "getOpponent: invalid given player";  // TODO
}

/**
 * Last cleaning before quitting.
 */
void Game::aboutToQuitApp() {
    // cleaning
}
