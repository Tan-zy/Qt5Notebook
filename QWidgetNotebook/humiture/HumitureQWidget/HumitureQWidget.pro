######################################################################
# Automatically generated by qmake (3.1) Fri Aug 2 21:36:20 2019
######################################################################

TEMPLATE = app
TARGET = HumitureQWidget
INCLUDEPATH += .

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += comconfig.h \
           doubledisplay.h \
           home.h \
           humiture.h \
           humiturecharts.h \
           humiturerecordpage.h \
           IM_modbus.h \
           modbustest.h \
           modifycmd.h \
           readcmd.h \
           singleconfig.h \
           singledisplay.h \
           Libmodbus/config.h \
           Libmodbus/modbus-private.h \
           Libmodbus/modbus-rtu-private.h \
           Libmodbus/modbus-rtu.h \
           Libmodbus/modbus-tcp-private.h \
           Libmodbus/modbus-tcp.h \
           Libmodbus/modbus-version.h \
           Libmodbus/modbus.h
FORMS += comconfig.ui \
         doubledisplay.ui \
         home.ui \
         humiture.ui \
         humiturerecordpage.ui \
         modbustest.ui \
         modifycmd.ui \
         readcmd.ui \
         singleconfig.ui \
         singledisplay.ui
SOURCES += comconfig.cpp \
           doubledisplay.cpp \
           home.cpp \
           humiture.cpp \
           humiturecharts.cpp \
           humiturerecordpage.cpp \
           IM_modbus.cpp \
           main.cpp \
           modbustest.cpp \
           modifycmd.cpp \
           readcmd.cpp \
           singleconfig.cpp \
           singledisplay.cpp \
           Libmodbus/modbus-data.c \
           Libmodbus/modbus-rtu.c \
           Libmodbus/modbus-tcp.c \
           Libmodbus/modbus.c
RESOURCES += img.qrc
