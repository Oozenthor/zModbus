#include "zmodbus.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ZModbus w;
    w.show();

    return a.exec();
}
