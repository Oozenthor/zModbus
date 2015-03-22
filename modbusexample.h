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

protected:
    ZModbus *mb;

private slots:
    void on_FC03_Button_clicked();

    void on_FC06_Button_clicked();

    void on_FC10_Button_clicked();

private:
    Ui::ModbusExample *ui;
};
#endif // MODBUSEXAMPLE

