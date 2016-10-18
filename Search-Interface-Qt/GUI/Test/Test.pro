#-------------------------------------------------
#
# Project created by QtCreator 2013-03-11T22:10:58
#
#-------------------------------------------------


include($$PWD/../Glyph.pri)
include($$PWD/../../Treemap/Treemap.pri)

INSTALL_PATH = /home/search-engine/install

QT          += widgets core gui opengl svg
TARGET      = Glyph
TEMPLATE    = app
DEFINES     += "DBG_GLYPH"
SOURCES     += $$PWD/Test.cpp

LIBS        += -L$${INSTALL_PATH}/lib  -lCommon -ltinyxml -lCache
INCLUDEPATH += $$PWD \
               $${INSTALL_PATH}/include/Common \
               $${INSTALL_PATH}/include/Cache \
