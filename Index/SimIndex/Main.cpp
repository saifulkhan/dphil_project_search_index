#include <QApplication>
#include "IndexManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IndexManager manager;
    manager.show();

    return a.exec();
}
