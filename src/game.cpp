#include <QDebug>
#include "game.h"
#include "playerremote.h"
#include "playerrandom.h"
#include "playernovice.h"
#include "playerminimax.h"

/**
 * Constructor
 *
 * @param parent a pointer to the parent
 */
Game::Game(player_t & p1, player_t & p2, QObject *parent) :
    QObject(parent),
    playerCounter(0)
{
    // Get the instance of the main application
    app = QCoreApplication::instance();

    // create essential objects

    board   = new Board(this);
    player1 = createPlayer(p1);
    player2 = createPlayer(p2);

    turn = player2;
}

/**
 * Main game function. Creates the objects of Player, Board, Piece.
 * Controls the game state.
 */
void Game::run() {
    Piece* piece = turn->choosePiece();
    board->deleteStock(piece);    
    qDebug() << turn->getName() << " chooses first piece: " << piece->toString();
    board->printStock();

    try {
        while (!board->checkVictory() && piece != NULL) {
            turn = getOpponent(turn);
            qDebug() << turn->getName() << "plays with piece: " << piece->toString();
            piece = turn->move(piece);
            qDebug() << turn->getName() << "chooses piece: " << ((piece == NULL) ? "NULL" : piece->toString());
            board->printMatrix();
            board->printStock();
        }
    } catch (const char * excpt) {
        qDebug() << excpt;
    }

    if (board->checkVictory()) { // someone has won
        qDebug() <<  turn->getName() << " has won!";
    } else { // draw
        qDebug() << "It is a draw!";
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
    playerCounter++;
    Player *retval = NULL;
    switch (player.type) {
    case RANDOM:
        retval = new PlayerRandom(QString(playerCounter+'0').append("-Random"), board, this);
        break;
    case NOVICE:
        retval = new PlayerNovice(QString(playerCounter+'0').append("-Novice"), board, this);
        break;
    case MINIMAX:
        retval = new PlayerMiniMax(QString(playerCounter+'0').append("-Minimax"), player.minimax_level ,board, this);
        break;
    case REMOTE:
        retval = new PlayerRemote(QString(playerCounter+'0').append("-Remote"), player.additional, board, this);  
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
