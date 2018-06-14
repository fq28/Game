TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
 QT += core

SOURCES += \
        main.cpp \
    object.cpp \
    enemy.cpp \
    player.cpp \
    levels.cpp \
    obstacles.cpp


QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
LIBS += -LC:/SFML/lib -LC:/SFML/bin
LIBS += -lsfml-network

INCLUDEPATH += C:/SFML/include
DEPENDPATH += C:/SFML/include

HEADERS += \
    object.h \
    enemy.h \
    player.h \
    levels.h \
    obstacles.h

RESOURCES += \
    game_2.qrc

