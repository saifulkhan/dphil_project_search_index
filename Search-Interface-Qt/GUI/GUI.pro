# Hierarchy / Branch tree
# Treemap <-contains- FSMapping <-contains- GUI
#
#-------------------------------------------------

INSTALL_PATH = /home/search-engine/install

QT         += widgets core gui opengl xml network
TARGET      = GUI
TEMPLATE    = app
CONFIG      += c++11
DEFINES     += \

SOURCES     += \
            $$PWD/Main.cpp \
            $$PWD/GUI.cpp \
            #$$PWD/Client.cpp \
            Table.cpp \
            View.cpp \
            #
            $$PWD/Glyph.cpp \
            $$PWD/Mapping.cpp \
            $$PWD/ColourMap.cpp \
            $$PWD/TransferFunction.cpp \
            $$PWD/Treemap.cpp \
            $$PWD/Tile.cpp \

HEADERS     += \
            $$PWD/GUI.h \
            #$$PWD/Client.h \
            Table.h \
            View.h \
            #
            $$PWD/Glyph.h \
            $$PWD/Mapping.h \
            $$PWD/ColourMap.h \
            $$PWD/TransferFunction.h \
            $$PWD/Treemap.h \
            $$PWD/Tile.h \

FORMS       += \
            $$PWD/GUI.ui \
            Mapping.ui \
            Treemap.ui


RESOURCES   += \
            $$PWD/Resources.qrc \
            $$PWD/Gnome.qrc \

LIBS        += -L$${INSTALL_PATH}/lib  -lQueryProcessor -lIndex -lOntology -lCommon -ltinyxml -lLanguageProcessor -lsparksee -ljson_spirit \

INCLUDEPATH += $$PWD \
               $${INSTALL_PATH}/include/QueryProcessor \
               $${INSTALL_PATH}/include/Common \
               $${INSTALL_PATH}/include/LanguageProcessor \
               $${INSTALL_PATH}/include/Ontology \
               $${INSTALL_PATH}/include/sparksee \
               $${INSTALL_PATH}/include/Index

exe.path       = $${INSTALL_PATH}/exe
exe.files      = $${OUT_PWD}/GUI
INSTALLS      += exe

# End
message(Qt Version          : $${QT_VERSION})
message(Target              : $${TARGET})
message(Source Directory    : $${PWD})
message(Build Directory     : $${OUT_PWD})
