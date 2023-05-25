#include "editemployee.h"
#include "ui_editemployee.h"

EditEmployee::EditEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditEmployee)
{
    ui->setupUi(this);
}

EditEmployee::~EditEmployee()
{
    delete ui;
}
