#-------------------------------------------------
#
# Project created by QtCreator 2018-10-22T21:25:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjetAW
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    game.cpp \
    player.cpp \
    map.cpp \
    cell.cpp \
    imageholder.cpp \
    units/unit.cpp \
    ui.cpp \
    buildings/buildings.cpp \
    buildings/citybuilding.cpp \
    buildings/factorybuilding.cpp \
    buildings/airportbuilding.cpp \
    units/LandUnits/bazooka.cpp \
    units/LandUnits/infantery.cpp \
    units/LandVehicles/recon.cpp \
    units/LandVehicles/antiair.cpp \
    units/LandVehicles/tank.cpp \
    units/LandVehicles/mdtank.cpp \
    units/LandVehicles/megatank.cpp \
    units/LandVehicles/neotank.cpp \
    units/AirUnits/bcopter.cpp \
    units/AirUnits/fighter.cpp \
    units/AirUnits/bomber.cpp

HEADERS += \
        mainwindow.h \
    game.h \
    player.h \
    map.h \
    cell.h \
    imageholder.h \
    units/unit.h \
    ui.h \
    buildings/buildings.h \
    buildings/citybuilding.h \
    buildings/factorybuilding.h \
    buildings/airportbuilding.h \
    units/LandUnits/bazooka.h \
    units/LandUnits/infantery.h \
    units/LandUnits/recon.h \
    units/LandUnits/bazooka.h \
    units/LandUnits/infantery.h \
    units/LandVehicles/recon.h \
    units/unit.h \
    units/LandVehicles/antiair.h \
    units/LandVehicles/tank.h \
    units/LandVehicles/mdtank.h \
    units/LandVehicles/megatank.h \
    units/LandVehicles/neotank.h \
    units/AirUnits/bcopter.h \
    units/AirUnits/fighter.h \
    units/AirUnits/bomber.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
