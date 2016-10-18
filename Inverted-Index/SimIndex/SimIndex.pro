#--------------------------------------------------------------
# Set FILE_SIM_DATA and FILE_SIM_LOC to for default location
#
#--------------------------------------------------------------

CONFIG      += c++11
QT          += widgets
TEMPLATE    = app

INSTALL_PATH = /home/search-engine/install

DEFINES     += DIR_CRAWL_DISK=\\\"/mnt\\\" \
               FILE_SIM_LOC=\\\"$$INSTALL_PATH/stat/\\\" \
               FILE_SIM_DATA=\\\"$$INSTALL_PATH/stat/Data.csv\\\" \


SOURCES     +=  $$PWD/IndexManager.cpp \
                $$PWD/Main.cpp \

HEADERS     += $$PWD/IndexManager.h \

FORMS       += $$PWD/IndexManager.ui \

LIBS        += -L$${INSTALL_PATH}/lib -lCommon -ltinyxml -lIndex \

INCLUDEPATH +=  $$PWD \
                $${INSTALL_PATH}/include/Common \
                $${INSTALL_PATH}/include/Index \

				
				
# Install
exe.path       = $${INSTALL_PATH}/exe \
exe.files      += $${OUT_PWD}/IndexManager \
INSTALLS       += exe \

# End
message(Target              : $${TEMPLATE})
message(Source Directory    : $${PWD})
message(Build Directory     : $${OUT_PWD})
message(Install Directory   : $${INSTALL_PATH})
message(LIBS:  $${LIBS})
message(HEADERS:  $${HEADERS})
