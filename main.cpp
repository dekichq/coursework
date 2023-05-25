#include "mainwindow.h"
#include <QApplication>
#include "sqlitedbmanager.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    DBManager* dbManager = SQLiteDBManager::getInstance();  //SqliteDBManager::getInstance();


    MainWindow window(dbManager);
    window.show();


    return application.exec();
}
