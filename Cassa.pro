#-------------------------------------------------
#
# Project created by QtCreator 2017-09-06T16:20:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cassa
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    Core/Context.cpp \
    Core/db/DatabaseConnection.cpp \
    Core/db/DatabaseQuery.cpp \
    Core/logs/Logger.cpp \
    Model/Product.cpp \
    Model/Order.cpp \
    Core/IStorageByIdModel.cpp \
    Core/IStorageModel.cpp \
    Model/OrderDetails.cpp \
    ViewModel/FormMainViewModel.cpp \
    Core/GuiUtils.cpp \
    ViewModel/FormOrderViewModel.cpp \
    ViewModel/orderitemviewmodel.cpp

HEADERS += \
    Core/Context.h \
    Core/db/DatabaseConnection.h \
    Core/db/DatabaseQuery.h \
    Core/logs/Logger.h \
    Model/Product.h \
    Model/Order.h \
    Core/IStorageByIdModel.h \
    Core/IStorageModel.h \
    Model/OrderDetails.h \
    ViewModel/FormMainViewModel.h \
    Core/GuiUtils.h \
    ViewModel/FormOrderViewModel.h \
    ViewModel/orderitemviewmodel.h

FORMS += \
    View/FormMain.ui \
    View/FormOrder.ui

INCLUDEPATH += $$PWD

if(win32*):CONFIG(debug, debug|release) {
    INCLUDEPATH += "C:/libs/sqlite-amalgamation-3200100"
    LIBS += -L "C:/libs/sqlite-dll-win32-x86-3200100" -l sqlite3
}
if(linux-g++*):CONFIG(debug, debug|release) {
    INCLUDEPATH += /usr/include
    LIBS += -L/usr/lib -L/usr/lib/nvidia-375 -lsqlite3 -lGL
}

UI_DIR += tmp
OBJECTS_DIR += tmp
MOC_DIR += tmp
