#include <QApplication>
#include <QDebug>
#include <QtGlobal>
#include "MainWindow.h"
#include "../Common/Common.h"


int main (int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile::remove (QString("TestResult.csv"));
    QFile::remove (QString("debuglog.txt"));
    qInstallMessageHandler( myMessageOutput );

    Stimuli::MainWindow *win = new Stimuli::MainWindow ();
    win->show();

    return a.exec();
}
