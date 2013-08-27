#include <QDebug>
#include "game.h"

/**
 * Constructor
 *
 * @param parent a pointer to the parent
 */
Game::Game(QObject *parent) : QObject(parent) {

    // Get the instance of the main application
    app = QCoreApplication::instance();

    // create essential objects
    player1 = new Player(this);
    player2 = new Player(this);
    board   = new Board(this);
    //piece   = new Piece(this);
}

/**
 * Main game function. Creates the objects of Player, Board, Piece.
 * Controls the game state.
 */
void Game::run() {
    qDebug() << "Game is running";                  // TODO delete

    quit();
}

/**
 * Quits the application
 */
void Game::quit() {
    emit finished();
}

/**
 * Last cleaning before quitting.
 */
void Game::aboutToQuitApp() {
    // cleaning
}
