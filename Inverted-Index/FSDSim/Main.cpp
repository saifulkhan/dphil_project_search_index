#include <QApplication>
#include "FSDSim.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FSDSim fsdsim;
    fsdsim.show();

    return a.exec();
}
