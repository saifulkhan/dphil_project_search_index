#-------------------------------------------------
include($$PWD/Treemap/Treemap.pri)

SOURCES += \
    $$PWD/QueryProcessor.cpp \
    $$PWD/Term.cpp \
    $$PWD/QueryParser.cpp \
    $$PWD/MachineLearning/NeuralNet.cpp \
    $$PWD/MachineLearning/RelevanceFeedback.cpp \

HEADERS  += \
    $$PWD/QueryProcessor.h \
    $$PWD/Term.h \
    $$PWD/QueryParser.h \
    $$PWD/MachineLearning/NeuralNet.h \
    $$PWD/MachineLearning/RelevanceFeedback.h \

INCLUDEPATH += $$PWD \
               $$PWD/MachineLearning \
