#include <QtCore/QCoreApplication>
#include <QTimer>
#include <iostream>

#include "game.h"
#include "common.h"
#include "optionparser/optionparser.h"
#include "playerrandom.h"


enum status_t {
    E_OK,
    E_HELP,
    E_CMD_ERROR
};

struct settings_t {
    status_t status;
    Player *players[PLAYER_COUNT];
};


enum optionIndex {
    UNKNOWN,
    HELP,
    RANDOM,
    NOVICE,
    MINIMAX,
    REMOTE,
    HUMAN
};

const option::Descriptor usage[] = {
    {UNKNOWN, 0, "",  "", option::Arg::None,     "USAGE: Quatro [OPTIONS] PLAYER PLAYER \n\n"
                                                 "Options:" },
    {HELP,    0, "h", "help", option::Arg::None, "  --help  \tPrint this text and exit.\n\n"
                                                 "Players:"},
    {RANDOM,  0, "", "random", option::Arg::None, "  --random, -p  \tRandom player." },
    {NOVICE,  0, "", "novice", option::Arg::None, "  --novice, -p  \tNovice player." },
    {MINIMAX, 0, "", "minimax", option::Arg::None, "  --minimax, -p  \tMinimax player with given depth level." },
    {REMOTE,  0, "", "remote", option::Arg::None, "  --remote, -p  \tRemote player on given port." },
    {HUMAN,   0, "", "human", option::Arg::None, "  --human, -p  \tHuman player." },
 //   {UNKNOWN, 0, "" ,  ""   , option::Arg::None, "\nExamples:\n"
 //                                                "  example --unknown -- --this_is_no_option\n"
 //                                                "  example -unk --plus -ppp file1 file2\n" },
      {0,0,0,0,0,0}
};

settings_t parse_cmd_params(int argc, char *argv[], QCoreApplication &app);

/**
 * Main program function
 */
int main(int argc, char *argv[])
{
    settings_t settings;
    QCoreApplication app(argc, argv);

    settings = parse_cmd_params(argc, argv, app);
    if (settings.status == E_HELP) {
        option::printUsage(std::cout, usage);
        return 0;
    } else if (settings.status == E_CMD_ERROR) {
        return 1;
    } else {

    }

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


settings_t parse_cmd_params(int argc, char *argv[], QCoreApplication &app)
{
    settings_t settings;

    settings.status = E_OK;
    // skip program name argv[0] if present
    argc -= (argc > 0);
    argv += (argc > 0);

    option::Stats  stats(usage, argc, argv);
    option::Option options[stats.options_max], buffer[stats.buffer_max];
    option::Parser parse(usage, argc, argv, options, buffer);

    if (parse.error()) {
        settings.status = E_CMD_ERROR;
        return settings;
    }

    if (options[HELP] || argc == 0) {
        settings.status = E_HELP;
        return settings;
    }

    for (option::Option* opt = options[UNKNOWN]; opt; opt = opt->next())
        std::cout << "Unknown option: " << opt->name << "\n";

    for (int i = 0; i < parse.nonOptionsCount(); ++i)
        std::cout << "Non-option #" << i << ": " << parse.nonOption(i) << "\n";


    if (options[UNKNOWN].count() > 0 || parse.nonOptionsCount() > 0) {
        settings.status = E_CMD_ERROR;
        return settings;
    }

    unsigned player_index = 0;

    for (int i = 0; i < parse.optionsCount(); ++i) {
        option::Option& opt = buffer[i];
        switch (opt.index()) {
            RANDOM:
                settings.players[player_index++] = new PlayerRandom(app);
            NOVICE:
            MINIMAX:
            REMOTE:
            HUMAN:
            default:
                throw "parse_cmd_params: unrecongized player type";
                break;
       }
    }

    return settings;
}
