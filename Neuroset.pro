QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += c++11  # only C++17 and above have std::any
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    #$$PWD/src/* \
    src/main.cpp \
    src/main-window.cpp \
    src/model.cpp \
    src/eeg-headset.cpp \
    src/event-queue.cpp \
    src/event.cpp \
    src/globals.cpp \
    src/interface.cpp \
    src/neureset-device.cpp \
    src/pc.cpp \
    src/pc-interface.cpp \
    src/session.cpp \
    src/user-interface.cpp \
    src/electrode.cpp \
    src/wave.cpp

HEADERS += \
    # $$PWD/headers/* \
    headers/main.h \
    headers/main-old.h \
    headers/main-window.h \
    headers/model.h \
    headers/eeg-headset.h \
    headers/event-queue.h \
    headers/event.h \
    headers/globals.h \
    headers/interface.h \
    headers/neureset-device.h \
    headers/pc.h \
    headers/pc-interface.h \
    headers/session.h \
    headers/user-interface.h \
    headers/electrode.h \
    headers/wave.h

FORMS += \
    forms/main-window.ui

INCLUDEPATH += $$PWD/headers


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
