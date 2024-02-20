QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    breachincidentcreation.cpp \
    logincident.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    malwareincident.cpp \
    phishincident.cpp \
    ransomwareincident.cpp \
    sqlite3.c

HEADERS += \
    breachincidentcreation.h \
    logincident.h \
    mainmenu.h \
    mainwindow.h \
    malwareincident.h \
    phishincident.h \
    ransomwareincident.h

FORMS += \
    breachincidentcreation.ui \
    logincident.ui \
    mainmenu.ui \
    mainwindow.ui \
    malwareincident.ui \
    phishincident.ui \
    ransomwareincident.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
