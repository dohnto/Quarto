#include <QtCore/QCoreApplication>
#include <QTimer>
#include "game.h"

/**
 * Main program function
 */
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // create the main class
    Game game(&app);

    // connect up the signals
    QObject::connect(&game,   SIGNAL(finished()),
                     &app,    SLOT(quit()));
    QObject::connect(&app,    SIGNAL(aboutToQuit()),
                     &game,   SLOT(aboutToQuitApp()));

    // Starts the execution after 10ms in the Game.run() routine.
    QTimer::singleShot(10, &game, SLOT(run()));

    return app.exec();
}
