#include <QApplication>
#include "CacheManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CacheManager cacheManager;
    cacheManager.show();

    return a.exec();
}
