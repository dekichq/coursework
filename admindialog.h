#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>
#include "dbmanager.h"

namespace Ui {
class AdminDialog;
}

class AdminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDialog(QWidget *parent = nullptr);
    ~AdminDialog();

private slots:
    void on_addEmployee_clicked();

    void on_employeesTable_clicked();

private:
    Ui::AdminDialog *ui;
    DBManager *db;
};

#endif // ADMINDIALOG_H
