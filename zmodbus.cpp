#include "zmodbus.h"
#include "ui_zmodbus.h"

ZModbus::ZModbus(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ZModbus)
{
    ui->setupUi(this);
}

ZModbus::~ZModbus()
{
    delete ui;
}
