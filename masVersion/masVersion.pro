QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
VERSION = 2020.10.18
RC_ICONS = icon.ico
#打印版本信息
message(qt version: $$QT_VERSION)

CONFIG += c++11

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
    abortwin.cpp \
    main.cpp \
    mainwindow.cpp \
    setwin.cpp

HEADERS += \
    abortwin.h \
    mainwindow.h \
    default.h \
    setwin.h

FORMS += \
    abortwin.ui \
    mainwindow.ui \
    setwin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    ModuleOwnersList\
平台模块名称编号对照表.txt\
平台模块名称负责人对照表.txt \
    CMD
