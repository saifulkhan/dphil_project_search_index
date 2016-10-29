#
# 1. Depends on the Common project.
# 2. We shall install all the binaries and data in the $HOME/install filder.
# 2. The generated dataset will be copied to $HOME/install.
# 3. $ sudo apt-get install libgl1-mesa-dev <-- to resolve the -lGL error
#

CONFIG   +=  c++11
QT       += widgets xml
TEMPLATE = app

INSTALL_PATH    = $$(HOME)/install

DEFINES +=      FILE_SIM_DATA=\\\"$$INSTALL_PATH/stat/Data.csv\\\" \
                FILE_LOR_ORG=\\\"$$PWD/Namespace.xml\\\" \
                FILE_NAME_STAT=\\\"$$PWD/Stat/Short-Dic.csv\\\" \
                FILE_TYPE_STAT=\\\"$$PWD/Stat/TypeStat.csv\\\" \
                FILE_USER_STAT=\\\"$$PWD/Stat/User.csv\\\" \
                FILE_GROUP_STAT=\\\"$$PWD/Stat/Group.csv\\\" \
                DIR_STAT_FILE=\\\"$$INSTALL_PATH/stat\\\" \



SOURCES     +=  $$PWD/Main.cpp \
                $$PWD/DataManager.cpp \
                $$PWD/GenSimFiles.cpp \
                $$PWD/GenSystemStat.cpp \
                $$PWD/Namespace.cpp \
                $$PWD/Distributions/DiscreteDist.cpp \
                $$PWD/Distributions/Weibull.cpp \
                $$PWD/Distributions/LogNormal.cpp \
                $$PWD/Distributions/Cauchy.cpp \
                $$PWD/Distributions/AbstractContDist.cpp \
                $$PWD/Distributions/ContDistFactory.cpp \
                $$PWD/Distributions/TimeDistribution.cpp \

HEADERS +=      $$PWD/DataManager.h \
                $$PWD/GenSimFiles.h \
                $$PWD/GenSystemStat.h \
                $$PWD/Namespace.h \
                $$PWD/Distributions/LogNormal.h \
                $$PWD/Distributions/DiscreteDist.h \
                $$PWD/Distributions/Weibull.h \
                $$PWD/Distributions/Cauchy.h \
                $$PWD/Distributions/AbstractContDist.h \
                $$PWD/Distributions/ContDistFactory.h \
                $$PWD/Distributions/TimeDistribution.h

FORMS +=        $$PWD/DataManager.ui


OTHER_FILES +=  $$HOME/install/stat/Data.csv \
                $$PWD/Stat/Group.csv \
                $$PWD/Stat/User.csv \
                $$PWD/Stat/Short-Dic.csv \
                $$PWD/Stat/TypeStat.csv \
                $$PWD/Namespace.xml \


LIBS +=         -L$${INSTALL_PATH}/lib -lCommon -ltinyxml

INCLUDEPATH +=  $$PWD \
                $${INSTALL_PATH}/include/Common

# Install
exe.files +=    $${OUT_PWD}/DataManager
exe.path  =     $${INSTALL_PATH}/exe
oth.files +=    $$OTHER_FILES
oth.path  =     $${INSTALL_PATH}/stat
INSTALLS  +=    exe oth

# End
message(Target              : $${TEMPLATE})
message(Source Directory    : $${PWD})
message(Build Directory     : $${OUT_PWD})
message(Install Directory   : $${INSTALL_PATH})


