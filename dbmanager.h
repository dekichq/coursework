#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QVariantList>
#include "employee.h"
#include "room.h"

class DBManager
{
public:
    DBManager();

    /* Методи для безпосередньої роботи з класом
     * Підключення до бази даних і вставка записів у таблицю
     * */
    virtual void connectToDataBase() = 0;
    virtual QSqlDatabase getDB() = 0;
    virtual bool insertIntoEmployeesTable(const Employee &employeeData) = 0;
    virtual bool insertIntoRoomsTable(const Room &roomsData) = 0;
    virtual bool deleteFromTable(const Employee &employeeData) = 0;
    virtual bool bookRoom(const Room &roomsData) = 0;
    virtual QString hashPassword(QString password) = 0;
    virtual bool checkLogPass(QString login, QString passwordHash) = 0;
};

#endif // DBMANAGER_H
