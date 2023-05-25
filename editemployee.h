#ifndef EDITEMPLOYEE_H
#define EDITEMPLOYEE_H

#include <QDialog>

namespace Ui {
class EditEmployee;
}

class EditEmployee : public QDialog
{
    Q_OBJECT

public:
    explicit EditEmployee(QWidget *parent = nullptr);
    ~EditEmployee();

private:
    Ui::EditEmployee *ui;
};

#endif // EDITEMPLOYEE_H
