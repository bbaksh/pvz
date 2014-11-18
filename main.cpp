#include "mainwindow.h"
#include <QApplication>
bool close;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
