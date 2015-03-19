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
    QList<quint16> readList = mb->ReadHoldingRegisters(1, 4);
    ui->lineEdit_1->setText(QString::number(readList[0]));
    ui->lineEdit_2->setText(QString::number(readList[1]));
    ui->lineEdit_3->setText(QString::number(readList[2]));
    ui->lineEdit_4->setText(QString::number(readList[3]));
}

void ModbusExample::on_FC06_Button_clicked()
{
    mb->WriteSingleRegister(1, 2);
}

void ModbusExample::on_FC10_Button_clicked()
{
//    mb->WriteMultipleRegisters()
}
