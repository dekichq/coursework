QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addemployee.cpp \
    admindialog.cpp \
    bookroomwindow.cpp \
    dbmanager.cpp \
    employee.cpp \
    employeestable.cpp \
    employeewindow.cpp \
    main.cpp \
    mainwindow.cpp \
    room.cpp \
    sqlitedbmanager.cpp

HEADERS += \
    addemployee.h \
    admindialog.h \
    bookroomwindow.h \
    dbmanager.h \
    employee.h \
    employeestable.h \
    employeewindow.h \
    mainwindow.h \
    room.h \
    sqlitedbmanager.h

FORMS += \
    addemployee.ui \
    admindialog.ui \
    bookroomwindow.ui \
    employeestable.ui \
    employeewindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
