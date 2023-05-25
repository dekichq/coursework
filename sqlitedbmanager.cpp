#include "sqlitedbmanager.h"
#include "admindialog.h"
#include "employeewindow.h"

#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QCryptographicHash>
#include <QSqlRecord>
#include <QMessageBox>

SQLiteDBManager* SQLiteDBManager::instance = nullptr;

SQLiteDBManager::SQLiteDBManager(){

}

SQLiteDBManager* SQLiteDBManager::getInstance()
{
    if(instance == nullptr){
        instance = new SQLiteDBManager();
    }
    return instance;
}

void SQLiteDBManager::connectToDataBase()
{

    if(QFile(DATABASE_NAME).exists()){
        this->openDataBase();
    } else {
        this->restoreDataBase();
    }
}

QSqlDatabase SQLiteDBManager::getDB()
{
    return db;
}


bool SQLiteDBManager::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTables()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не вдалось відновити базу даних";
        return false;
    }
}

bool SQLiteDBManager::openDataBase()
{

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(DATABASE_NAME);
    if(db.open()){
        return true;
    } else
        return false;
}

void SQLiteDBManager::closeDataBase()
{
    db.close();
}


bool SQLiteDBManager::createTables()
{

    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " EMPLOYEES_TABLE_NAME " ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    EMPLOYEES_NAME          " TEXT              NOT NULL,"
                    EMPLOYEES_SURNAME       " TEXT              NOT NULL,"
                    EMPLOYEES_LOGIN         " TEXT              NOT NULL,"
                    EMPLOYEES_PASSWORD      " TEXT              NOT NULL,"
                    EMPLOYEES_PASSWORD_HASH " TEXT              NOT NULL"
                    " )"
                    )){
        qDebug() << "DataBase: error of create " << EMPLOYEES_TABLE_NAME;
        qDebug() << query.lastError().text();
        return false;
    } else {
        if(!query.exec( "CREATE TABLE " ROOMS_TABLE_NAME " ("
                        ROOMS_NUMBER                " TEXT          NOT NULL, "
                        ROOMS_FLOOR                 " TEXT          NOT NULL, "
                        ROOMS_CLIENT_PHONE          " TEXT          , "
                        ROOMS_CLIENT_NAME           " TEXT          , "
                        ROOMS_TIME                  " TEXT          , "
                        ROOMS_PRICE                 " TEXT          NOT NULL, "
                        ROOMS_NUMBER_OF_BEDS        " TEXT          NOT NULL "
                        " )"
                    )){
            qDebug() << "DataBase: error of create " << ROOMS_TABLE_NAME;
            qDebug() << query.lastError().text();
            return false;
        } else {
        Employee admin;
        Employee worker;
        worker.setName("123");
        worker.setSurname("123");
        worker.setLogin("123");
        worker.setPassword("123");
        admin.setName("admin");
        admin.setSurname("admin");
        admin.setLogin("admin");
        admin.setPassword("admin");
        connectToDataBase();

        insertIntoEmployeesTable(admin);
        insertIntoEmployeesTable(worker);

        for(int a = 0; a < 10; a++) {
            Room room;
            int floor, number;
            number = a + 1;
            int numberOfBeds;
            if(numberOfBeds >= 3) {
                numberOfBeds = 1;
            } else
                numberOfBeds = numberOfBeds + 1;
            if(a < 5) {
                floor = 1;
            } else
                floor = 2;
            room.setNumber(number);
            room.setFloor(floor);
            room.setPrice(number*1000);
            room.setNumberOfBeds(numberOfBeds);

            insertIntoRoomsTable(room);
        }
        return true;
        }

}
}

bool SQLiteDBManager::insertIntoEmployeesTable(const Employee &employeedata)
{

    QSqlQuery query;
    QString passwordHash = hashPassword(employeedata.getPassword());
        query.prepare("INSERT INTO Employees ( " EMPLOYEES_NAME ", "
                      EMPLOYEES_SURNAME ", "
                      EMPLOYEES_LOGIN ", "
                      EMPLOYEES_PASSWORD " , "
                      EMPLOYEES_PASSWORD_HASH " ) "
                                            "VALUES (:Name, :Surname, :Login, :Password, :PasswordHash)");
        query.bindValue(":Name",            employeedata.getName());
        query.bindValue(":Surname",         employeedata.getSurname());
        query.bindValue(":Login",           employeedata.getLogin());
        query.bindValue(":Password",        employeedata.getPassword());
        query.bindValue(":PasswordHash",    passwordHash);





    if(!query.exec()){
        qDebug() << "error insert into employees table";
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();

        return false;
    } else
        return true;
}

bool SQLiteDBManager::deleteFromTable(const Employee &employeedata)
{
    QSqlQuery query;

    query.prepare("DELETE FROM " EMPLOYEES_TABLE_NAME " WHERE " EMPLOYEES_NAME " = :name AND " EMPLOYEES_SURNAME " = :surname");
    query.bindValue(":name", employeedata.getName());
    query.bindValue(":surname", employeedata.getSurname());

    if(!query.exec()) {
        qDebug() << "error delete from employees table";
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        return false;
    } else
        return true;
}

bool SQLiteDBManager::checkLogPass(QString login, QString password) {
    QSqlQuery query;
    password = hashPassword(password);
    query.prepare("SELECT Password FROM Employees WHERE login = :login AND passwordHash = :password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if(query.exec()) {
        int count = 0;
        while(query.next()) {
            count++;
        }
        if (count == 1) {
            QMessageBox msg;
            msg.setText("Всі дані правильні, заходжу у систему");
            msg.exec();
            if(login == ADMIN_LOGIN) {
                if(password == ADMIN_PASSWORD_HASH) {
                    AdminDialog dialog;
                    dialog.setModal(true);
                    dialog.exec();
                }
            } else {
                EmployeeWindow dialog;
                dialog.setModal(true);
                dialog.exec();
            }
        }

        if (count < 1) {
            QMessageBox msg;
            msg.setText("Неправильний логін чи пароль");
            msg.exec();
        }

    }


    if(!query.exec()){
        qDebug() << "error check log pass";
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();

        return false;
    } else
        return true;
};

bool SQLiteDBManager::insertIntoRoomsTable(const Room &roomsData) {
    QSqlQuery query;
        query.prepare("INSERT INTO " ROOMS_TABLE_NAME" ( " ROOMS_NUMBER ", "
                      ROOMS_FLOOR ", "
                      ROOMS_PRICE ", "
                      ROOMS_NUMBER_OF_BEDS " ) "
                                            "VALUES (:Number, :Floor, :Price, :NumberOfBeds)");
        query.bindValue(":Number",          roomsData.getNumber());
        query.bindValue(":Floor",           roomsData.getFloor());
        query.bindValue(":Price",           roomsData.getPrice());
        query.bindValue(":NumberOfBeds",    roomsData.getNumberOfBeds());


    if(!query.exec()){
        qDebug() << "error insert into rooms table";
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();

        return false;
    } else
        return true;
}

bool SQLiteDBManager::bookRoom(const Room &roomsData) {
    QSqlQuery query;
    query.prepare("UPDATE " ROOMS_TABLE_NAME
                  " SET " ROOMS_CLIENT_NAME " = :clientName , "
                  ROOMS_CLIENT_PHONE " = :clientPhone , "
                  ROOMS_TIME " = :time WHERE " ROOMS_NUMBER " = :number ");

    query.bindValue(":clientName",      roomsData.getClientName());
    query.bindValue(":clientPhone",     roomsData.getClientPhone());
    query.bindValue(":time",            roomsData.getTime());
    query.bindValue(":number",          roomsData.getNumber());

    if(!query.exec()){
        qDebug() << "error update rooms table";
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();

        return false;
    } else
        return true;
}


QString SQLiteDBManager::hashPassword(QString password) {
    QString hash;
    QByteArray hashpassword(password.toStdString().c_str());
    hash = QCryptographicHash::hash(hashpassword, QCryptographicHash::Sha256).toHex();
    return hash;
}
