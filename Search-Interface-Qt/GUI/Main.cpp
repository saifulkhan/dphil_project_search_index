#include <QApplication>
#include "GUI.h"
#include "Table.h"

void test_client();
void test_tableView();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GUI gui;
    gui.show();

    return a.exec();
}
