#ifndef ADDEMPLOYEE_H
#define ADDEMPLOYEE_H

#include <QDialog>

class DBManager;
namespace Ui {
class AddEmployee;
}



class AddEmployee : public QDialog
{
    Q_OBJECT

public:
    explicit AddEmployee(QWidget *parent = nullptr);
    ~AddEmployee();

private slots:
    void on_addEmployee_clicked();

private:
    Ui::AddEmployee *ui;
    DBManager *db;
};

#endif // ADDEMPLOYEE_H
