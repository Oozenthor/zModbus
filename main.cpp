#include "modbusexample.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ModbusExample w;
    w.show();

    return a.exec();
}
