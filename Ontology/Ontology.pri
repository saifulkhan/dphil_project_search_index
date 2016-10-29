#-------------------------------------------------

CONFIG      += c++11
CONFIG      -= qt
TEMPLATE     = lib \

INSTALL_PATH = /home/search-engine/install
DEFINES      += \
            GDB_CFG=\\\"$$INSTALL_PATH/conf/Configuration.cfg\\\" \
            TERM_ONTOLOGY=\\\"$$INSTALL_PATH/gdb/TermOntology.gdb\\\" \
            TYPE_ONTOLOGY=\\\"$$INSTALL_PATH/gdb/TypeOntology.gdb\\\" \
            SIZE_ONTOLOGY=\\\"$$INSTALL_PATH/gdb/SizeOntology.gdb\\\" \

HEADERS += \
    $$PWD/OntologyFactory.h \
    $$PWD/Ontology.h \
    $$PWD/TypeOntology.h \
    $$PWD/TermOntology.h \
    $$PWD/SizeOntology.h

SOURCES += \
    $$PWD/OntologyFactory.cpp \
    $$PWD/Ontology.cpp \
    $$PWD/TypeOntology.cpp \
    $$PWD/TermOntology.cpp \
    $$PWD/SizeOntology.cpp

OTHER_FILES += \
    $$PWD/License/Configuration.cfg
