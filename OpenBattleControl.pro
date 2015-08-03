#-------------------------------------------------
#
# Project created by QtCreator 2015-08-01T22:23:57
#
#-------------------------------------------------

QT		+= core gui
QT		+= serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenBattleControl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    iconnector.cpp \
    serialportconnector.cpp \
    logger.cpp

HEADERS  += mainwindow.h \
    iconnector.h \
    serialportconnector.h \
    rulestab.h \
    ../libraries/OpenBattleCore/Generated.h \
    ../libraries/OpenBattleCore/OpenBattleCore.h \
    informationmessagehandler.h \
    logger.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libraries/OpenBattleCore/lib/release/ -lOpenBattleCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libraries/OpenBattleCore/lib/debug/ -lOpenBattleCore
else:unix: LIBS += -L$$PWD/../libraries/OpenBattleCore/lib/ -lOpenBattleCore

INCLUDEPATH += $$PWD/../libraries/OpenBattleCore
#DEPENDPATH += $$PWD/../libraries/OpenBattleCore

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../libraries/OpenBattleCore/lib/release/libOpenBattleCore.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../libraries/OpenBattleCore/lib/debug/libOpenBattleCore.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../libraries/OpenBattleCore/lib/release/OpenBattleCore.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../libraries/OpenBattleCore/lib/debug/OpenBattleCore.lib
else:unix: PRE_TARGETDEPS += $$PWD/../libraries/OpenBattleCore/lib/libOpenBattleCore.a
