#include "admindialog.h"
#include "ui_admindialog.h"
#include "addemployee.h"
#include "employeestable.h"

AdminDialog::AdminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog)
{
    ui->setupUi(this);
}

AdminDialog::~AdminDialog()
{
    delete ui;
}

void AdminDialog::on_addEmployee_clicked()
{
    AddEmployee dialog;
    dialog.setModal(true);
    dialog.exec();
}


void AdminDialog::on_employeesTable_clicked()
{
    EmployeesTable dialog;
    dialog.setModal(true);
    dialog.exec();
}

