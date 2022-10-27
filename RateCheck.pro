QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    appManager.cpp \
    main.cpp \
    mainwindow.cpp \
    support/start_stop_watch.cpp \
    support/benchmark.cpp \
    support/file_manager.cpp


unix:DEFINES += LINUX
DEFINES += GCC Foundation_EXPORTS
win32:DEFINES += WIN64
HEADERS += \
    appManager.h \
    appVersion.h \
    mainwindow.h \
    support/benchmark.h \
    support/start_stop_watch.h \
    support/file_manager.h

FORMS += \
    mainwindow.ui

macx: {
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15
}

HOMEDIR = "../"

CONFIG(debug, debug|release) {
    OBJECTS_DIR = Debug
    DESTDIR = Debug
}
else {
    OBJECTS_DIR = Release
    DESTDIR = Release
}

INCLUDEPATH = support/poco/include \
              support

unix:!macx {
    DEFINES += NOT_MAC
}

macx: {
    DEFINES += MAC_OS
}

win32:LIBS += -lversion -lIphlpapi -lSetupApi -lNewdev -lws2_32

ICON = icon.png

RESOURCES += \
    resource.qrc



