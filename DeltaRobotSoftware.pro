QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camerawidget.cpp \
    connectionmanager.cpp \
    connectionsettings.cpp \
    deltavisualizer.cpp \
    gcodeprogrammanager.cpp \
    gcodewindow.cpp \
    hsvwindow.cpp \
    imageprocessor.cpp \
    main.cpp \
    mainwindow.cpp \
    objectmanager.cpp \
    objectvariabletable.cpp

HEADERS += \
    camerawidget.h \
    connectionmanager.h \
    connectionsettings.h \
    deltavisualizer.h \
    gcodeprogrammanager.h \
    gcodewindow.h \
    hsvwindow.h \
    imageprocessor.h \
    mainwindow.h \
    objectmanager.h \
    objectvariabletable.h

FORMS += \
    connectionsettings.ui \
    gcodewindow.ui \
    hsvwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc

DISTFILES +=

win32:CONFIG(release, debug|release): LIBS += -LD:/ProgramFile/opencv/opencv/build/x64/vc16/lib/ -lopencv_world490
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/ProgramFile/opencv/opencv/build/x64/vc16/lib/ -lopencv_world490d

INCLUDEPATH += D:/ProgramFile/opencv/opencv/build/include
DEPENDPATH += D:/ProgramFile/opencv/opencv/build/include
