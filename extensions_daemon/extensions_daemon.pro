QT += core dbus
QT -= gui

TARGET = extensions_daemon
CONFIG   += console link_pkgconfig
PKGCONFIG += gq-gconf
INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/telepathy-1.0

TEMPLATE = app

SOURCES += main.cpp \
           controller.cpp

HEADERS += \
           controller.h

target.path = /opt/status-menu-extensions/bin

INSTALLS += target
