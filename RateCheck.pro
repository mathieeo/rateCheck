QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    support/start_stop_watch.cpp \
    support/benchmark.cpp \
    support/file_manager.cpp


unix:DEFINES += LINUX
DEFINES += GCC Foundation_EXPORTS
win32:DEFINES += WIN64
HEADERS += \
    mainwindow.h \
    support/benchmark.h \
    support/start_stop_watch.h \
    support/file_manager.h

FORMS += \
    mainwindow.ui


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


#LIBS += -L$$HOMEDIR/Lib/Gcc

win32:LIBS += -lversion -lIphlpapi -lSetupApi -lNewdev -lws2_32

