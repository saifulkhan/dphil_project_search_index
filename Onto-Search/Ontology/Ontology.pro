#-------------------------------------------------

include(Ontology.pri)

CONFIG      += c++11
CONFIG      -= qt
TEMPLATE     = lib \

LIBS        += -L$${INSTALL_PATH}/lib  -lCommon -ltinyxml -lsparksee

INCLUDEPATH += $$PWD \
               $${INSTALL_PATH}/include/sparksee \
               $${INSTALL_PATH}/include/Common \

# Install
headers.path    = $${INSTALL_PATH}/include/Ontology
headers.files   += $${HEADERS}
libs.path       = $${INSTALL_PATH}/lib
libs.files      += $${OUT_PWD}/libOntology.so
confs.path      = $${INSTALL_PATH}/conf
confs.files     += $${OTHER_FILES}
INSTALLS        += headers libs confs

# End
message(Target              : $${TEMPLATE})
message(Source Directory    : $${PWD})
message(Build Directory     : $${OUT_PWD})
message(Install Directory   : $${INSTALL_PATH})
