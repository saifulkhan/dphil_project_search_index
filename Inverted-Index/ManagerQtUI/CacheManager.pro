#-------------------------------------------------


#-------------------------------------------------

CONFIG      += c++11
QT          += widgets
TEMPLATE    = app

INSTALL_PATH = /home/search-engine/install

DEFINES     += DIR_CRAWL_DISK=\\\"/mnt\\\" \
               FILE_SIM_DATA=\\\"$$INSTALL_PATH/stat/Data.csv\\\"

SOURCES     +=  $$PWD/CacheManager.cpp \
                $$PWD/Manager.cpp \

HEADERS     += $$PWD/CacheManager.h

FORMS       += $$PWD/CacheManager.ui

LIBS        += -L$${INSTALL_PATH}/lib -lCommon -ltinyxml -lCache

INCLUDEPATH +=  $$PWD \
                $${INSTALL_PATH}/include/Common \
                $${INSTALL_PATH}/include/Cache \
				
				
# Install
exe.path       = $${INSTALL_PATH}/exe
exe.files      += $${OUT_PWD}/CacheManager
INSTALLS       += exe

# End
message(Target              : $${TEMPLATE})
message(Source Directory    : $${PWD})
message(Build Directory     : $${OUT_PWD})
message(Install Directory   : $${INSTALL_PATH})
