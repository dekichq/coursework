#ifndef EMPLOYEEWINDOW_H
#define EMPLOYEEWINDOW_H

#include <QDialog>

class QSqlTableModel;

namespace Ui {
class EmployeeWindow;
}

class EmployeeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EmployeeWindow(QWidget *parent = nullptr);
    ~EmployeeWindow();
    int getRow(int row);

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_bookRoom_clicked();

    void on_exit_clicked();

private:
    Ui::EmployeeWindow *ui;
    QSqlTableModel *model;

    int row;
private:
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
};

#endif // EMPLOYEEWINDOW_H
