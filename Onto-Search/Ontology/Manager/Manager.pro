#-------------------------------------------------

#include(../Ontology.pri)
INSTALL_PATH = /home/search-engine/install

TARGET      = OntologyManager
TEMPLATE    = app
CONFIG      += c++11
CONFIG      -= qt
TEMPLATE    += app
DEFINES     += \
             #"DBG_GDB"

SOURCES  += \
           Manager.cpp

LIBS        += -L$${INSTALL_PATH}/lib -lCommon -lOntology -lsparksee -ltinyxml
INCLUDEPATH +=  $${INSTALL_PATH}/include/Common \
                $${INSTALL_PATH}/include/Ontology \

exe.path       = $${INSTALL_PATH}/exe
exe.files     += $${OUT_PWD}/OntologyManager
INSTALLS      += exe

# End
message(Target            : $${TARGET})
message(Source Directory  : $${PWD})
message(Build Directory   : $${OUT_PWD})
message(Install Directory : $${INSTALL_PATH})
