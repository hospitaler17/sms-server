QT -= gui

QT += network
CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        libs/adminkeymodulewrapper.cpp \
        main.cpp \
        maincontroller.cpp \
        message/checker.cpp \
        ethernet/transportlayer.cpp \
        ethernet/applicationlayer.cpp \
        ethernet/httppacket.cpp \
        modem/modem.cpp \
        modem/modemscontroller.cpp \
        storage/logger.cpp \
        storage/settings.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    common.h \
    libs/adminkeymodulewrapper.h \
    maincontroller.h \
    message/checker.h \
    ethernet/transportlayer.h \
    ethernet/applicationlayer.h \
    ethernet/httppacket.h \
    modem/modem.h \
    modem/modemscontroller.h \
    storage/logger.h \
    storage/settings.h

INCLUDEPATH += \
    modem \
    ethernet \
    message \
    storage \
    libs


TARGET = "sms-server"

