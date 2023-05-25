#ifndef BOOKROOMWINDOW_H
#define BOOKROOMWINDOW_H

#include <QDialog>

namespace Ui {
class bookRoomWindow;
}

class bookRoomWindow : public QDialog
{
    Q_OBJECT

public:
    explicit bookRoomWindow(QWidget *parent = nullptr);
    ~bookRoomWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::bookRoomWindow *ui;
};

#endif // BOOKROOMWINDOW_H
