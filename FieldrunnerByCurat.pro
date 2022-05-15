QT       += core gui multimedia xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 resources_big

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    barrier.cpp \
    bullet.cpp \
    card.cpp \
    configreader.cpp \
    eliminate.cpp \
    enemie.cpp \
    flyer.cpp \
    gattling.cpp \
    glue.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    mousehouse.cpp \
    runner.cpp \
    stubbornrunner.cpp \
    tower.cpp \
    towerpos.cpp \
    upgrade.cpp

HEADERS += \
    barrier.h \
    bullet.h \
    card.h \
    configreader.h \
    eliminate.h \
    enemie.h \
    enemieGlobal.h \
    flyer.h \
    gattling.h \
    global.h \
    glue.h \
    mainwindow.h \
    map.h \
    mousehouse.h \
    runner.h \
    stubbornrunner.h \
    tower.h \
    towerGolbal.h \
    towerpos.h \
    upgrade.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc



