#include "mainwindow.h"
#include "connection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c ;
    bool test = c.createconnection();
    MainWindow w;
    w.show();
    return a.exec();
}
