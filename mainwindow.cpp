#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dbmanager.h"
#include "sqlitedbmanager.h"

MainWindow::MainWindow(DBManager* dbManager, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    db(dbManager)
{
    ui->setupUi(this);

    db->connectToDataBase();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString log = ui->login->text();
    QString pass = ui->password->text();
    DBManager *db = SQLiteDBManager::getInstance();

    if(db->checkLogPass(log, pass)){
        close();
    }
}

