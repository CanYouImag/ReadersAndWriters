QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# 添加编码设置
win32: MSVC {
    QMAKE_CXXFLAGS += /utf-8
    QMAKE_CFLAGS += /utf-8
} else {
    QMAKE_CXXFLAGS += -finput-charset=UTF-8 -fexec-charset=UTF-8
    QMAKE_CFLAGS += -finput-charset=UTF-8 -fexec-charset=UTF-8
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    readerwriter.cpp \
    scheduler.cpp \
    writerPreference.cpp \
    readerpreference.cpp \
    fair.cpp

HEADERS += \
    mainwindow.h \
    readerwriter.h \
    scheduler.h \
    writerPreference.h \
    readerpreference.h \
    fair.h \
    common.h \
    debuginfo.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
