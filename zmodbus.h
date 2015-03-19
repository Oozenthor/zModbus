#ifndef ZMODBUS_H
#define ZMODBUS_H

#include <QMainWindow>

namespace Ui {
class ZModbus;
}

class ZModbus : public QMainWindow
{
    Q_OBJECT

public:
    explicit ZModbus(QWidget *parent = 0);
    ~ZModbus();

private:
    Ui::ZModbus *ui;
};

#endif // ZMODBUS_H
