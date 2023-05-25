#include "bookroomwindow.h"
#include "ui_bookroomwindow.h"
#include "room.h"
#include "dbmanager.h"
#include "sqlitedbmanager.h"

#include <QMessageBox>

bookRoomWindow::bookRoomWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bookRoomWindow)
{
    ui->setupUi(this);
}

bookRoomWindow::~bookRoomWindow()
{
    delete ui;
}

void bookRoomWindow::on_pushButton_clicked()
{
    QString clientPhone, clientName, time;
    int number = ui->roomNumber->text().toInt();
    clientPhone = ui->clientPhone->text();
    clientName = ui->clientName->text();
    time = ui->time->text();
    Room client;
    client.setNumber(number);
    client.setClientName(clientName);
    client.setClientPhone(clientPhone);
    client.setTime(time);
    DBManager *db = SQLiteDBManager::getInstance();
    if(db->bookRoom(client)) {
        QMessageBox msg;
        msg.setText("Номер заброньовано!");
        msg.exec();
        close();
    }

}

