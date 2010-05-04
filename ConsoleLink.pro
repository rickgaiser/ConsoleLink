# -------------------------------------------------
# Project created by QtCreator 2009-04-06T21:17:03
# -------------------------------------------------
QT += network
TARGET = ConsoleLink
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    debug.cpp \
    ps2FileServer.cpp \
    ps2Command.cpp \
    ps2Screenshot.cpp
HEADERS += mainwindow.h \
    debug.h \
    hostlink.h \
    byteorder.h \
    ps2FileServer.h \
    ps2Command.h \
    ps2Screenshot.h
FORMS += mainwindow.ui \
    about.ui \
    settings.ui
RESOURCES += ConsoleLink.qrc
