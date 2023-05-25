#include "employeewindow.h"
#include "ui_employeewindow.h"
#include "dbmanager.h"
#include "sqlitedbmanager.h"
#include "bookroomwindow.h"

#include <QSqlTableModel>

EmployeeWindow::EmployeeWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeWindow)
{
    ui->setupUi(this);
    this->setupModel(ROOMS_TABLE_NAME,
                     QStringList() << tr("Номер")
                                   << tr("Поверх")
                                   << tr("Номер клієнта")
                                   << tr("Ім'я клієнта")
                                   << tr("Час перебування")
                                   << tr("Ціна за одну ніч")
                                   << tr("Кількість ліжок")
               );
    this->createUI();
}

EmployeeWindow::~EmployeeWindow()
{
    delete ui;
}

void EmployeeWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    DBManager *db = SQLiteDBManager::getInstance();
    model = new QSqlTableModel(this, db->getDB());
    model->setTable(tableName);

    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    model->setSort(0,Qt::AscendingOrder);
}

void EmployeeWindow::createUI()
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

void EmployeeWindow::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}


void EmployeeWindow::on_bookRoom_clicked()
{
    bookRoomWindow dialog;
    dialog.setModal(true);
    if(!dialog.exec()) {
        createUI();
    }
}



