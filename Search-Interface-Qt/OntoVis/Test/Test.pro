INSTALL_PATH = /home/search-engine/install

include($$PWD/../OntoVis.pri)

QT          += widgets core gui opengl
TARGET      = Test
TEMPLATE    = app
CONFIG      += c++11
DEFINES     += "DBG_ONTOVIS"

SOURCES     += $$PWD/Test.cpp


LIBS        += -L$${INSTALL_PATH}/lib  -lOntology

#-lCommon -lCache -ltinyxml -lsparksee -lQueryProcessor

INCLUDEPATH += $$PWD \
               $${INSTALL_PATH}/include/Common \
               $${INSTALL_PATH}/include/Ontology \
               $${INSTALL_PATH}/include/sparksee
# End
message(Qt Version          : $${QT_VERSION})
message(Target              : $${TARGET})
message(Source Directory    : $${PWD})
message(Build Directory     : $${OUT_PWD})


