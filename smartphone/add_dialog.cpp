#include "add_dialog.h"
#include "ui_add_dialog.h"
#include "smartphone.h"

Add_Dialog::Add_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_Dialog)
{
    ui->setupUi(this);
    setFixedSize(size());
    setWindowTitle(" ");
}

Add_Dialog::~Add_Dialog()
{
    delete ui;
}

void Add_Dialog::setName(QString arg) {
    ui->lineEdit->setText(arg);
}

void Add_Dialog::setModel(QString arg) {
    ui->lineEdit_2->setText(arg);
}

void Add_Dialog::setManufacturer(QString arg) {
    ui->lineEdit_3->setText(arg);
}

void Add_Dialog::setMemory(QString arg) {
    ui->lineEdit_4->setText(arg);
}

void Add_Dialog::setYear(QString arg) {
    ui->lineEdit_5->setText(arg);
}

Smartphone Add_Dialog::getData() {
    Smartphone result;

    result.setName(ui->lineEdit->text().simplified());
    result.setModel(ui->lineEdit_2->text().simplified());
    result.setManufacturer(ui->lineEdit_3->text().simplified());
    result.setMemory(ui->lineEdit_4->text().simplified());
    result.setYear(ui->lineEdit_5->text().simplified());


    return result;
}

void Add_Dialog::on_buttonBox_accepted()
{

}

