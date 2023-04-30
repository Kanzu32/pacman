QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

CONFIG += c++17 exception

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    game.cpp \
    help.cpp \
    main.cpp \
    records.cpp \
    settings.cpp \
    settingsdialog.cpp \
    widget.cpp

HEADERS += \
    direction.h \
    game.h \
    help.h \
    level.h \
    movable.h \
    records.h \
    settings.h \
    settingsdialog.h \
    widget.h

FORMS += \
    game.ui \
    help.ui \
    records.ui \
    settings.ui \
    settingsdialog.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=
