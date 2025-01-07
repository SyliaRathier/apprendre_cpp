QT += core gui widgets quick quickwidgets positioning location
# QT       += core gui quickwidgets qml
#QT += core gui
# QT += widgets
# QT += network
# QT += core gui network
# QT += core gui concurrent
# QT += location positioning

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    car.cpp \
    edge.cpp \
    graph.cpp \
    graphview.cpp \
    jsonreader.cpp \
    main.cpp \
    mainwindow.cpp \
    mapoverlay.cpp \
    node.cpp \
    utils.cpp

HEADERS += \
    car.h \
    edge.h \
    graph.h \
    graphview.h \
    jsonreader.h \
    mainwindow.h \
    mapoverlay.h \
    node.h \
    utils.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
