#-------------------------------------------------

include($$PWD/QueryProcessor.pri)
INSTALL_PATH = /home/search-engine/install

CONFIG      += c++11
CONFIG      -= qt
TEMPLATE     = lib \
DEFINES     += #"DBG_QP"

INCLUDEPATH += $$PWD \
               $${INSTALL_PATH}/include/Cache \
               $${INSTALL_PATH}/include/Common \
               $${INSTALL_PATH}/include/Ontology \
               $${INSTALL_PATH}/include/sparksee \

LIBS        += -L$${INSTALL_PATH}/lib  -lCommon -lCache -lOntology -lsparksee -ltinyxml -ljson_spirit


# Install
headers.path = $${INSTALL_PATH}/include/QueryProcessor
headers.files= $${HEADERS}
so.path      = $${INSTALL_PATH}/lib
so.files     = $${OUT_PWD}/*.so
INSTALLS    += headers so

# End
message(Target              : $${TEMPLATE})
message(Source Directory    : $${PWD})
message(Build Directory     : $${OUT_PWD})
message(Install Directory   : $${INSTALL_PATH})

SOURCES += \
    Test/Test.cpp

OTHER_FILES += \
    Test/CMakeLists.txt \
    CMakeLists.txt
