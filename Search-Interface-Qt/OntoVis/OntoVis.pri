#
# http://qt-project.org/doc/qt-4.8/graphicsview-elasticnodes.html
#

INSTALL_PATH = /home/search-engine/install

HEADERS     += $$PWD/Edge.h \
               $$PWD/Node.h \
               $$PWD/GraphWidget.h

SOURCES     += $$PWD/Edge.cpp \
               $$PWD/Node.cpp \
               $$PWD/GraphWidget.cpp

FORMS       += #$$PWD/GUI.ui \

RESOURCES   += #$$PWD/Resources.qrc \

#LIBS       += -L$${INSTALL_PATH}/lib  -lCommon -lCache -ltinyxml -lOntology -lsparksee -lQueryProcessor
INCLUDEPATH += $$PWD \



