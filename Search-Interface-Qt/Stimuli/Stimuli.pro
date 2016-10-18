#-------------------------------------------------
#
# Project created by QtCreator 2013-01-02T20:56:30
#
#-------------------------------------------------

# Tested with Qt version: Qt 4.8.4


QT       += core gui

TARGET = Stimuli
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += main.cpp \
    MainWindow.cpp \
    TestA.cpp \
    TestB.cpp \
    TestC.cpp \
    Global.cpp \
    ../GUI/Glyph/Animation.cpp \
    ../GUI/Glyph/SecondaryGlyph.cpp \
    ../GUI/Glyph/Secondary.cpp \
    ../GUI/GlobalVariables.cpp \
    ../GUI/Glyph/Glyph.cpp \
    ../Common/Common.cpp \

HEADERS  += \
    MainWindow.h \
    TestA.h \
    TestB.h \
    TestC.h \
    Global.h \
    ../GUI/Glyph/Animation.h \
    ../GUI/Glyph/SecondaryGlyph.h \
    ../GUI/Glyph/Secondary.h \
    ../GUI/GlobalVariables.h \
    ../GUI/Glyph/Glyph.h \
    ../Common/Common.h

FORMS += \
    MainWindow.ui \
    TestB.ui \
    TestC.ui \
    TestA.ui

RESOURCES += \
    Stimuli.qrc


win32 {
    #LIBS += -LD:\Repositories\search-project\Visualization -ltext
    INCLUDEPATH += "D:\Dropbox\DPhil-Research\Code\search-project\Visualization" \
                   "D:\Dropbox\DPhil-Research\Code\search-project\Search-Engine" \

}
