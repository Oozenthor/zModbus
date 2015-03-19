#ifndef MODBUSEXAMPLE
#define MODBUSEXAMPLE
#include "zmodbus.h"

#include <QDialog>

namespace Ui {
class ModbusExample;
}

class ModbusExample : public QDialog
{
    Q_OBJECT

public:
    explicit ModbusExample(QWidget *parent = 0);
    ~ModbusExample();

private:
    Ui::ModbusExample *ui;
    ZModbus *mb;
};
#endif // MODBUSEXAMPLE

