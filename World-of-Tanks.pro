QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gui/cggrass.cpp \
    gui/cgimprovements.cpp \
    gui/cgshell.cpp \
    gui/cgtank.cpp \
    gui/gamewindow.cpp \
    gui/icgobject.cpp \
    gui/mainwindow.cpp \
    logic/cgame.cpp \
    logic/cgrass.cpp \
    logic/cimprovements.cpp \
    logic/cmap.cpp \
    logic/cshell.cpp \
    logic/ctank.cpp \
    logic/icmovableobject.cpp \
    logic/icobject.cpp \
    logic/icstaticobject.cpp \
    logic/main.cpp

HEADERS += \
    cwall.h \
    gui/cggrass.h \
    gui/cgimprovements.h \
    gui/cgshell.h \
    gui/cgtank.h \
    gui/gamewindow.h \
    gui/icgobject.h \
    gui/mainwindow.h \
    logic/cgame.h \
    logic/cgrass.h \
    logic/cimprovements.h \
    logic/cmap.h \
    logic/cshell.h \
    logic/ctank.h \
    logic/icmovableobject.h \
    logic/icobject.h \
    logic/icstaticobject.h

FORMS += \
    gui/gamewindow.ui \
    gui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    gui/images/resources.qrc
