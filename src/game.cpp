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

    board   = new Board(this);
    player1 = createPlayer(p1);
    player2 = createPlayer(p2);

    turn = player2;

    //piece   = new Piece(this);
}

/**
 * Main game function. Creates the objects of Player, Board, Piece.
 * Controls the game state.
 */
void Game::run() {
    Piece* piece = turn->choosePiece();
    qDebug() << piece->toString();

    //board->debugFillMatrix();

    for (unsigned i = 0; i < 3; i++) {                                  // TODO change
        turn = getOpponent(turn);
        piece = turn->move(piece);
        board->printMatrix();
        board->printStock();
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
 * @brief Game::createPlayer creates a player according to given structure
 * @param player
 * @return
 */
Player *Game::createPlayer(struct player_t &player)
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
