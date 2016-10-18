TARGET          = Data
TEMPLATE        = app
QT              += core xml
CONFIG          += c++11
INSTALL_PATH    = /home/search-engine/install
DIR_STAT_FILE   = $$INSTALL_PATH/stat

DEFINES         += \
                FILE_SIM_DATA=\\\"$$DIR_STAT_FILE/Data.csv\\\" \
                FILE_LOR_ORG=\\\"$$DIR_STAT_FILE/Namespace.xml\\\" \
                FILE_TYPE_STAT=\\\"$$DIR_STAT_FILE/TypeStat.csv\\\" \
                FILE_NAME_STAT=\\\"$$DIR_STAT_FILE/Short-Dic.csv\\\" \
                DIR_STAT_FILE=\\\"$$INSTALL_PATH/stat\\\" \
                #"DBG_DATA" \
                #"TEST_DIST" \

SOURCES += \
    GenSimFiles.cpp \
    GenSystemStat.cpp \
    Namespace.cpp \
    Distributions/DiscreteDist.cpp \
    Distributions/Weibull.cpp \
    Distributions/LogNormal.cpp \
    Distributions/Cauchy.cpp \
    Distributions/AbstractContDist.cpp \
    Distributions/ContDistFactory.cpp \
    Distributions/TimeDistribution.cpp \
    Main.cpp

HEADERS += \
    GenSimFiles.h \
    GenSystemStat.h \
    Namespace.h \
    Distributions/LogNormal.h \
    Distributions/DiscreteDist.h \
    Distributions/Weibull.h \
    Distributions/Cauchy.h \
    Distributions/AbstractContDist.h \
    Distributions/ContDistFactory.h \
    Distributions/TimeDistribution.h

OTHER_FILES += \
    $$PWD/Namespace.xml \
    $$PWD/Stat/Short-Dic.csv \
    $$PWD/Stat/TypeStat.csv \


LIBS        += -L$${INSTALL_PATH}/lib -lCommon -ltinyxml
INCLUDEPATH += $$PWD \
               $${INSTALL_PATH}/include/Common \

exe.path    = $${INSTALL_PATH}/exe
exe.files   += $${OUT_PWD}/Data
oth.path    = $${INSTALL_PATH}/stat
oth.files   += $$OTHER_FILES

INSTALLS    += exe oth

# End
message(Target              : $${TARGET})
message(Source Directory    : $${PWD})
message(Build Directory     : $${OUT_PWD})

