QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    facade.cpp \
    fisher.cpp \
    graphworker.cpp \
    harmonic.cpp \
    main.cpp \
    mainwindow.cpp \
    matrix.cpp \
    qcustomplot.cpp \
    timeSeries.cpp \
    trend.cpp

HEADERS += \
    facade.h \
    fisher.h \
    graphworker.h \
    harmonic.h \
    mainwindow.h \
    matrix.h \
    qcustomplot.h \
    timeSeries.h \
    trend.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    econometrickQT.pro.user \
    table.csv
