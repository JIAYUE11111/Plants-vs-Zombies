QT       += core gui
QT       += widgets multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    animate.cpp \
    aspectratiolayout.cpp \
    coordinate.cpp \
    gameleveldata.cpp \
    gamescene.cpp \
    imagemanager.cpp \
    main.cpp \
    mainscene.cpp \
    mainwindow.cpp \
    mouseeventspixmapitem.cpp \
    plant.cpp \
    plantcarditem.cpp \
    timer.cpp \
    zombie.cpp

HEADERS += \
    animate.h \
    aspectratiolayout.h \
    coordinate.h \
    gameleveldata.h \
    gamescene.h \
    imagemanager.h \
    mainscene.h \
    mainwindow.h \
    mouseeventspixmapitem.h \
    plant.h \
    plantcarditem.h \
    timer.h \
    zombie.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    FinalWork2.qrc
