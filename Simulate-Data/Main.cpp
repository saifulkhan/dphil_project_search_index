#include <QApplication>
#include "DataManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DataManager manager;
    manager.show();

    return a.exec();
}
