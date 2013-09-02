#-------------------------------------------------
#
# Project created by QtCreator 2013-08-26T22:07:04
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Quarto
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    game.cpp \
    board.cpp \
    player.cpp \
    piece.cpp \
    playerrandom.cpp \
    playernovice.cpp \
    playerminimax.cpp \
    playerremote.cpp

HEADERS += \
    game.h \
    board.h \
    player.h \
    piece.h \
    common.h \
    playerrandom.h \
    playernovice.h \
    playerminimax.h \
    optionparser/optionparser.h \
    playerremote.h
