#ifndef EMPLOYEESTABLE_H
#define EMPLOYEESTABLE_H

#include <QDialog>

class QSqlTableModel;

namespace Ui {
class EmployeesTable;
}

class EmployeesTable : public QDialog
{
    Q_OBJECT

public:
    explicit EmployeesTable(QWidget *parent = nullptr);
    ~EmployeesTable();

private slots:
    void on_deleteEmployee_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_exit_clicked();

private:
    Ui::EmployeesTable *ui;
    QSqlTableModel *model;

    int row;
private:
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
};

#endif // EMPLOYEESTABLE_H
