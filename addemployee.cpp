#include "addemployee.h"
#include "ui_addemployee.h"
#include "dbmanager.h"
#include "sqlitedbmanager.h"
#include <QMessageBox>

AddEmployee::AddEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEmployee)
{
    ui->setupUi(this);
}

AddEmployee::~AddEmployee()
{
    delete ui;
}

void AddEmployee::on_addEmployee_clicked()
{
   Employee employeedata;
   employeedata.setName(ui->name->text());
   employeedata.setSurname(ui->surname->text());
   employeedata.setLogin(ui->login->text());
   employeedata.setPassword(ui->password->text());
   DBManager *db = SQLiteDBManager::getInstance();

   if(db->insertIntoEmployeesTable(employeedata)){
       QMessageBox msg;
       msg.setText("Працівника додано успішно!");
       msg.exec();
       close();
   }
}

