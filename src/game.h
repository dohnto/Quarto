#ifndef GAME_H
#define GAME_H

#include <QtCore/QCoreApplication>
#include <QObject>
#include "player.h"
#include "playerrandom.h"
#include "board.h"
#include "piece.h"
#include "common.h"

class Game : public QObject
{
    Q_OBJECT
public:

    /// Constructor.
    explicit Game(player_t & p1, player_t & p2, QObject *parent = 0);

    /// Quitting the application.
    void quit();

private:
    QCoreApplication *app;  /**< ??? TODO */
    Player *turn;           /**< whose turn is it */

    Player  *player1;
    Player  *player2;
    Board   *board;
    
    Player *getOpponent(Player *);
    Player *createPlayer(struct player_t & player);
    bool checkVictory();
signals:
    /// Finishes the application.
    void finished();

public slots:
    /// Starts the actual application (called from main).
    void run();

    /// Called by QCoreAppliction before quitting.
    void aboutToQuitApp();
    
};

#endif // GAME_H
