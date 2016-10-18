#-------------------------------------------------
#
# Project created by QtCreator 2012-12-25T18:49:05
#
#-------------------------------------------------
INSTALL_PATH = /home/search-engine/install

CONFIG      += c++11
CONFIG      -= qt
TEMPLATE     = lib \

SOURCES     += \
                QueryProcessorAddon.cpp \
                QueryProcessorWrapper.cpp \
                Test/Wrapper.cpp


HEADERS     += \
                QueryProcessorWrapper.h \
                Test/Wrapper.h


OTHER_FILES +=  binding.gyp \
                Test/Wrapper.js

exe.path  = $${INSTALL_PATH}/lib
exe.files+= $${OUT_PWD}/*.so
INSTALLS += exe

# End

message(Target              : $${TARGET})
message(Source Directory    : $${PWD})
message(Build Directory     : $${OUT_PWD})
message(Qt Version          : $${QT_VERSION})

