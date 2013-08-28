#include <QDebug>
#include "game.h"

/**
 * Constructor
 *
 * @param parent a pointer to the parent
 */
Game::Game(player_t & p1, player_t & p2, QObject *parent) : QObject(parent)
{
    // Get the instance of the main application
    app = QCoreApplication::instance();

    // create essential objects

    player1 = createPlayer(p1);
    player2 = createPlayer(p2);

    turn = player2;

    board   = new Board(this);
    //piece   = new Piece(this);
}

/**
 * Main game function. Creates the objects of Player, Board, Piece.
 * Controls the game state.
 */
void Game::run() {
    Piece* piece = turn->choosePiece();
    for (unsigned i = 0; i < 3; i++) {                                  // TODO change
        qDebug() << "---------------------";
        turn = getOpponent(turn);
        piece = turn->move(piece);
        // check situation                          // TODO
    }

    // TODO debug - smazat!
    board->debugFillMatrix();
    board->printMatrix();
    board->printStock();

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

Player *Game::createPlayer(player_t &player)
{
    Player *retval = NULL;
    switch (player.type) {
    case RANDOM:
        retval = new PlayerRandom(board, this);
        break;
    // TODO
    default:
        throw "NOT IMPLEMENTED";
        break;
    }

    return retval;
}

/**
 * Last cleaning before quitting.
 */
void Game::aboutToQuitApp() {
    // cleaning
}
