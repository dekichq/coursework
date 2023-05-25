#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

#include "dbmanager.h"
#include "employee.h"
#include "room.h"

#define DATABASE_HOSTNAME                       "DataBase"
#define DATABASE_NAME                           "ProjectDB.db"

#define EMPLOYEES_TABLE_NAME                    "Employees"
#define EMPLOYEES_NAME                          "Name"
#define EMPLOYEES_SURNAME                       "Surname"
#define EMPLOYEES_LOGIN                         "Login"
#define EMPLOYEES_PASSWORD_HASH                 "PasswordHash"
#define EMPLOYEES_PASSWORD                      "Password"

#define ROOMS_TABLE_NAME                        "Rooms"
#define ROOMS_NUMBER                            "Number"
#define ROOMS_FLOOR                             "Floor"
#define ROOMS_CLIENT_PHONE                      "ClientPhone"
#define ROOMS_CLIENT_NAME                       "ClientName"
#define ROOMS_TIME                              "Time"
#define ROOMS_PRICE                             "Price"
#define ROOMS_NUMBER_OF_BEDS                    "NumberOfBeds"

#define ADMIN_LOGIN                             "admin"
#define ADMIN_PASSWORD_HASH                     "8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918"

class SQLiteDBManager : public DBManager {

public:
    static SQLiteDBManager* getInstance();


    void connectToDataBase();
    QSqlDatabase getDB();
    bool insertIntoEmployeesTable(const Employee &employeeData);
    bool insertIntoRoomsTable(const Room &roomsData);
    bool deleteFromTable(const Employee &employeeData);
    bool bookRoom(const Room &roomsData);
    bool checkLogPass(QString login, QString passwordHash);
    QString hashPassword(QString password);

private:
    QSqlDatabase    db;

private:

    static SQLiteDBManager* instance;

    SQLiteDBManager();

    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTables();

};



#endif // DATABASE_H
