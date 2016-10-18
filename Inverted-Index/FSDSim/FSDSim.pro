
CONFIG   +=  c++11
QT       += widgets xml
TEMPLATE = app

INSTALL_PATH    = /home/search-engine/install

DEFINES +=      FILE_SIM_DATA=\\\"$$INSTALL_PATH/stat/Data.csv\\\" \
                FILE_LOR_ORG=\\\"$$PWD/Namespace.xml\\\" \
                FILE_NAME_STAT=\\\"$$PWD/Stat/Short-Dic.csv\\\" \
                FILE_TYPE_STAT=\\\"$$PWD/Stat/TypeStat.csv\\\" \
                FILE_USER_STAT=\\\"$$PWD/Stat/User.csv\\\" \
                FILE_GROUP_STAT=\\\"$$PWD/Stat/Group.csv\\\" \
                DIR_STAT_FILE=\\\"$$INSTALL_PATH/stat\\\" \



SOURCES     +=  $$PWD/Main.cpp \
                $$PWD/FSDSim.cpp \
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

HEADERS +=      $$PWD/FSDSim.h \
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

FORMS +=        $$PWD/FSDSim.ui


OTHER_FILES +=  $$PWD/Stat/Group.csv \
                $$PWD/Stat/User.csv \
                $$PWD/Stat/Short-Dic.csv \
                $$PWD/Stat/TypeStat.csv \
                $$PWD/Namespace.xml \


LIBS +=         -L$${INSTALL_PATH}/lib -lCommon -ltinyxml

INCLUDEPATH +=  $$PWD \
                $${INSTALL_PATH}/include/Common

# Install
exe.files +=    $${OUT_PWD}/FSDSim
exe.path  =     $${INSTALL_PATH}/exe
oth.files +=    $$OTHER_FILES
oth.path  =     $${INSTALL_PATH}/stat
INSTALLS  +=    oth

# End
message(Target              : $${TEMPLATE})
message(Source Directory    : $${PWD})
message(Build Directory     : $${OUT_PWD})
message(Install Directory   : $${INSTALL_PATH})


