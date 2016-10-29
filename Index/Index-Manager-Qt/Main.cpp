#include <QApplication>
#include "IndexManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IndexManager im;
    im.show();

    return a.exec();
}
