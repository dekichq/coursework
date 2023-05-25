#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>

class Employee
{
    QString name;
    QString surname;
    QString login;
    QString password;
    QString passwordHash;
public:
    void setName(QString name) {
        this->name = name;
    }
    QString getName() const {
        return this->name;
    }
    void setSurname(QString surname) {
        this->surname = surname;
    }
    QString getSurname() const {
        return this->surname;
    }
    void setLogin(QString login) {
        this->login = login;
    }
    QString getLogin() const {
        return this->login;
    }
    void setPassword(QString password) {
        this->password = password;
    }
    QString getPassword() const {
        return this->password;
    }
    void setPasswordHash(QString passwordHash) {
        this ->passwordHash = passwordHash;
    }
    QString getPasswordHash() const {
        return this->passwordHash;
    }
    Employee();
};

#endif // EMPLOYEE_H
