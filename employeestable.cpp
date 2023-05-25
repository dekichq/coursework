#include "employeestable.h"
#include "ui_employeestable.h"
#include "dbmanager.h"
#include "sqlitedbmanager.h"
#include "mainwindow.h"

#include <QSqlTableModel>

EmployeesTable::EmployeesTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeesTable)
{
    ui->setupUi(this);
    this->setupModel(EMPLOYEES_TABLE_NAME,
                     QStringList() << tr("id")
                                   << tr("Ім'я")
                                   << tr("Прізвище")
                                   << tr("Логін")
                                   << tr("Пароль")
                                   << tr("ХешПаролю")
               );
    this->createUI();
}

EmployeesTable::~EmployeesTable()
{
    delete ui;
}

void EmployeesTable::on_deleteEmployee_clicked()
{
    model->removeRow(row);
}


void EmployeesTable::setupModel(const QString &tableName, const QStringList &headers)
{
    DBManager *db = SQLiteDBManager::getInstance();
    model = new QSqlTableModel(this, db->getDB());
    model->setTable(tableName);

    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    model->setSort(0,Qt::AscendingOrder);
}

void EmployeesTable::createUI()
{
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    model->select();
}



void EmployeesTable::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}


