#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "add_dialog.h"
#include "show_data.h"
#include "QFileInfo"
#include "QFileDialog"
#include "QTextStream"
#include "Vector.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_New_triggered()
{
    if (ui->tableWidget->rowCount() > 0) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите создать новый файл?\nВсе проделанные изменения не будут сохранены.");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        if (msgBox.exec() == QMessageBox::No) {
            return;
        }
    }
    ui->tableWidget->setRowCount(0);
    main_vector.clear();
    file_ = "";
    setWindowTitle("*" + file_ + " – Функции языка программирования");
}

void MainWindow::on_action_Exit_triggered()
{
    if (ui->tableWidget->rowCount() > 0 || file_ != "") {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите выйти?\nВсе проделанные изменения не будут сохранены.");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        if (msgBox.exec() == QMessageBox::No) {
            return;
        }
    }
    exit(0);
}

void MainWindow::on_action_About_triggered()
{
    QMessageBox::about(this,
                       "О программе",
                       "Курсовая работа по дисциплине ООП\n"
                       "Тема: Класс, характеризующий смартфон\n"
                       "Вариант 24\n"
                       "Выполнил студент группы ИКПИ-24\n"
                       "Тимаев Александр\n"
                       "Санкт-Петербург\n"
                       "2023 год");
}

void MainWindow::on_action_Add_triggered()
{
    Add_Dialog myDialog;
    if (myDialog.exec() == QDialog::Accepted)
    {
        Smartphone t = myDialog.getData();

        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(t.getName()));
        //ui->tableWidget->item(ui->tableWidget->rowCount() - 1, 0)->setTextColor(FunctionType);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(t.getModel()));

        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(t.getManufacturer()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem(t.getYear()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, new QTableWidgetItem(t.getMemory()));
        //ui->tableWidget->item(ui->tableWidget->rowCount() - 1, 4)->setTextColor(FunctionComment);
        main_vector.push_back(t);
        ui->statusBar->showMessage("Запись добавлена");
        setWindowTitle("*" + file_ + " – характеристики смартфона");
    }
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->tableWidget->setCurrentCell(-1, -1);
    if (arg1 == "") {
        return;
    }
    ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);
    auto find_items = ui->tableWidget->findItems(arg1, Qt::MatchContains);
    int len = find_items.size();
    for (int i = 0; i < len; ++i) {
        auto item = find_items.at(i);
        ui->tableWidget->setRangeSelected(QTableWidgetSelectionRange(item->row(), 0, item->row(), 0), true);
    }
    ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->statusBar->showMessage("Найдено " + QString::number(len) + " ячеек");
}

void MainWindow::on_action_Edit_triggered()
{
    auto list = ui->tableWidget->selectedItems();
    if (list.size() > 0) {
        Add_Dialog myDialog;
        myDialog.setName(list.at(0)->text());
        myDialog.setModel(list.at(1)->text());
        myDialog.setManufacturer(list.at(2)->text());
        myDialog.setMemory(list.at(3)->text());
        myDialog.setYear(list.at(4)->text());

        if (myDialog.exec() == QDialog::Accepted)
        {
            Smartphone t = myDialog.getData();
            list.at(0)->setText(t.getName());
            list.at(1)->setText(t.getModel());
            list.at(2)->setText(t.getManufacturer());
            list.at(3)->setText(t.getMemory());
            list.at(4)->setText(t.getYear());

            main_vector[list.at(0)->row()].setName(t.getName());
            main_vector[list.at(1)->row()].setModel(t.getModel());
            main_vector[list.at(2)->row()].setManufacturer(t.getManufacturer());
            main_vector[list.at(3)->row()].setMemory(t.getMemory());
            main_vector[list.at(4)->row()].setYear(t.getYear());
            ui->statusBar->showMessage("Запись отредактирована");
            setWindowTitle("*" + file_ + " – Характеристики смартфона");
        }
    }
}

void MainWindow::on_action_Delete_triggered()
{
    auto list = ui->tableWidget->selectionModel()->selectedRows();
    if (list.size() > 0) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите удалить строки с выбранными элементами?");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        if (msgBox.exec() == QMessageBox::Yes) {
            for (auto k = list.rbegin(); k != list.rend(); ++k) {
                auto idx = (*k).row();
                main_vector.erase(idx);
                ui->tableWidget->removeRow(idx);
            }
            ui->statusBar->showMessage("Запись удалена");
            setWindowTitle("*" + file_ + " – характеристики смартфона");
        }
    } else ui->statusBar->showMessage("Таблица пуста");
}

void MainWindow::on_action_Clear_triggered()
{
    if (ui->tableWidget->rowCount() > 0) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите очистить таблицу?");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        if (msgBox.exec() == QMessageBox::Yes) {
            ui->tableWidget->setRowCount(0);
            main_vector.clear();
            ui->statusBar->showMessage("Таблица очищена");
            setWindowTitle("*" + file_ + " – характеристики смартфона");
        }
    } else ui->statusBar->showMessage("Таблица пуста");
}

void MainWindow::on_action_Open_triggered(bool isClean)
{
    QString file_name = QFileDialog::getOpenFileName(this, "Открыть файл...", ".", "CSV files (*.csv);;All files (*.*);;");
    QFileInfo check_file(file_name);

    if (check_file.exists() && check_file.isFile()) {
        if (isClean) {
            MainWindow::on_action_New_triggered();
        }

        QFile file(file_name);
        if (file.open(QIODevice::ReadOnly)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                Smartphone t;
                QString line = in.readLine();
                QStringList fields = line.split(";");

                if (fields.size() == 5) {
                    t.setName(fields[0].simplified());
                    t.setModel(fields[1].simplified());
                    t.setManufacturer(fields[2].simplified());
                    t.setMemory(fields[3].simplified());
                    t.setYear(fields[4].simplified());

                    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(t.getName()));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(t.getModel()));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(t.getManufacturer()));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem(t.getMemory()));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, new QTableWidgetItem(t.getYear()));

                    main_vector.push_back(t);
                }
            }
            file.close();
            ui->statusBar->showMessage("Записи из файла добавлены");
            file_ = file_name;
            setWindowTitle(file_ + " – характеристики смартфона");
        } else {
            ui->statusBar->showMessage("Файл '" + file_name + "' не удалось открыть на чтение (" + file.errorString() + ")");
        }
    } else {
        ui->statusBar->showMessage("Файл '" + file_name + "' не существует");
    }
}


void MainWindow::on_action_Save_triggered()
{
    if (file_ == "") {
        MainWindow::on_action_SaveAs_triggered();
        return;
    }
    QFile file(file_);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        int len = ui->tableWidget->rowCount();
        for (int i = 0; i < len; ++i) {
            QString name = ui->tableWidget->item(i, 0)->text();
            QString model = ui->tableWidget->item(i, 1)->text();
            QString manufacturer = ui->tableWidget->item(i, 2)->text();
            QString memory = ui->tableWidget->item(i, 3)->text();
            QString year = ui->tableWidget->item(i, 4)->text();
            out << name << ";" << model << ";" << manufacturer << ";" << memory << ";" << year << "\n";
        }
        file.close();
        ui->statusBar->showMessage("Файл записан");
        setWindowTitle(file_ + " – характеристики смартфона");
    }
}

void MainWindow::on_action_SaveAs_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Сохранить файл...", ".", "CSV files (*.csv);;All files (*.*);;");
    if (file_name != "") {
        file_ = file_name;
        MainWindow::on_action_Save_triggered();
    }
}

void MainWindow::on_action_Merge_triggered()
{
    QString old_file = file_;
    MainWindow::on_action_Open_triggered(false);
    file_ = old_file;
    ui->statusBar->showMessage("Данные объединены");
    setWindowTitle("*" + file_ + " – характеристики смартфона");
}

void MainWindow::on_tableWidget_cellDoubleClicked(int, int)
{
    MainWindow::on_action_Edit_triggered();
}

void MainWindow::on_action_ShowData_triggered()
{
    Show_Data myDialog;
    QString s;
    for (auto &k : main_vector) {
        s += k.getName() + ";" + k.getModel() + ";"  +  k.getManufacturer() + k.getMemory() + k.getYear() + "\n";
    }
    myDialog.setText(s);
    myDialog.exec();
}
