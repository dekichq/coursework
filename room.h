#ifndef ROOM_H
#define ROOM_H

#include <QString>

class Room
{
private:
    int number;
    int floor;
    QString clientPhone;
    QString clientName;
    QString time;
    int price;
    int numberOfBeds;
public:
    void setNumber(int number) {
        this->number = number;
    }
    void setFloor(int floor) {
        this->floor = floor;
    }
    void setClientPhone(QString clientPhone) {
        this->clientPhone = clientPhone;
    }
    void setClientName(QString clientName) {
        this->clientName = clientName;
    }
    void setTime(QString time) {
        this->time = time;
    }
    void setPrice(int price) {
        this->price = price;
    }
    void setNumberOfBeds(int numberOfBeds) {
        this->numberOfBeds = numberOfBeds;
    }
    int getNumber() const{
        return this->number;
    }
    int getFloor() const{
        return this->floor;
    }
    QString getClientPhone() const{
        return this->clientPhone;
    }
    QString getClientName() const{
        return this->clientName;
    }
    QString getTime() const{
        return this->time;
    }
    int getPrice() const{
        return this->price;
    }
    int getNumberOfBeds() const{
        return this->numberOfBeds;
    }


    Room();
};

#endif // ROOM_H
