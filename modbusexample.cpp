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

void ModbusExample::on_FC03_Button_clicked()
{
    mb->ReadHoldingRegisters(1, 1);
}

void ModbusExample::on_FC06_Button_clicked()
{
    mb->WriteSingleRegister(1, 2);
}

void ModbusExample::on_FC10_Button_clicked()
{
//    mb->WriteMultipleRegisters()
}
