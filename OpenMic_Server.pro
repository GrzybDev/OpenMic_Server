QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/net/listener.cpp \
    src/net/listeners/command.cpp \
    src/net/network.cpp \
    src/net/packet.cpp \
    src/net/packet_client.cpp \
    src/net/packets/hello.cpp \
    src/ui/MainWindow/mainwindow.cpp

HEADERS += \
    src/net/listener.h \
    src/net/listeners/command.h \
    src/net/network.h \
    src/net/packet.h \
    src/net/packet_client.h \
    src/net/packets/hello.h \
    src/ui/MainWindow/mainwindow.h

FORMS += \
    src/ui/MainWindow/mainwindow.ui

TRANSLATIONS += \
    src/lang/OpenMic_Server_en_US.ts \
    src/lang/OpenMic_Server_pl_PL.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS += src/res/icon.ico

VERSION = 0.0.1
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
