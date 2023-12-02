#ifndef ADD_DIALOG_H
#define ADD_DIALOG_H

#include <QDialog>
#include "smartphone.h"

namespace Ui {
    class Add_Dialog;
}

class Add_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Add_Dialog(QWidget *parent = nullptr);
    ~Add_Dialog();
    Smartphone getData();
    void setName(QString arg);
    void setModel(QString arg);
    void setManufacturer(QString arg);
    void setMemory(QString arg);
    void setYear(QString arg);
private slots:
    void on_buttonBox_accepted();

private:
    Ui::Add_Dialog *ui;
};

#endif // ADD_DIALOG_H
