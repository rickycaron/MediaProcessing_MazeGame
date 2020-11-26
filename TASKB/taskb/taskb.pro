QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    command.cpp \
    commandcontroller.cpp \
    genemy.cpp \
    ghealthpack.cpp \
    gprotagonist.cpp \
    gtile.cpp \
    main.cpp \
    moveup.cpp \
    widget.cpp

HEADERS += \
    command.h \
    commandcontroller.h \
    genemy.h \
    ghealthpack.h \
    gprotagonist.h \
    gtile.h \
    moveup.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

unix:!macx: LIBS += -L$$PWD/../world_v4/ -lworld

INCLUDEPATH += $$PWD/../world_v4
DEPENDPATH += $$PWD/../world_v4
