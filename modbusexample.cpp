#include "modbusexample.h"
#include "ui_modbusexample.h"

ModbusExample::ModbusExample(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModbusExample)
{
    ui->setupUi(this);
    mb = new ZModbus(this);
}

ModbusExample::~ModbusExample()
{
    delete ui;
}
