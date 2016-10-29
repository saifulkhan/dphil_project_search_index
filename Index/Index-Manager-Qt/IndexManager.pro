#
# Check the INSTALL_PATH is consistant with other modules, i.e., $HOME/install
#

CONFIG      += c++11
QT          += widgets
TEMPLATE    = app

INSTALL_PATH = $$(HOME)/install

DEFINES     += DIR_CRAWL_DISK=\\\"/mnt\\\" \
               FILE_SIM_DATA=\\\"$$INSTALL_PATH/stat/Data.csv\\\"

SOURCES     +=  $$PWD/IndexManager.cpp \
                $$PWD/Main.cpp \

HEADERS     += $$PWD/IndexManager.h

FORMS       += $$PWD/IndexManager.ui

LIBS        += -L$${INSTALL_PATH}/lib -lIndex -lLanguageProcessor -lCommon -ltinyxml

INCLUDEPATH +=  $$PWD \
                $${INSTALL_PATH}/include/Index \
                $${INSTALL_PATH}/include/LanguageProcessor \
                $${INSTALL_PATH}/include/Common \


				
				
# Install
exe.path       = $${INSTALL_PATH}/exe
exe.files      += $${OUT_PWD}/IndexManager
INSTALLS       += exe

# End
message(Target              : $${TEMPLATE})
message(Source Directory    : $${PWD})
message(Build Directory     : $${OUT_PWD})
message(Install Directory   : $${INSTALL_PATH})
