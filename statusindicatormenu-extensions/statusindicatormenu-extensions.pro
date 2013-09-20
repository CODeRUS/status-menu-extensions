TEMPLATE      = lib
QT += core dbus network
CONFIG       += plugin gui meegotouch link_pkgconfig iodata cellular-qt mobility
MOBILITY += connectivity

TARGET        = statusindicatormenu-extensions

PKGCONFIG += gq-gconf \
             accounts-qt \
             contextprovider-1.0

LIBS += -ltelepathy-qt4
LIBS += -lcellular-qt
LIBS += -lcreds
LIBS += -lX11

INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/cellular-qt
INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/telepathy-1.0
INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/accounts-qt
INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/meegotouch
INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/system-ui/statusindicatormenu
INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/contextprovider

target.path = /usr/lib/meegotouch/applicationextensions

png.files = icons/icon-extensions-background.png \
            icons/icon-extensions-power.png \
            icons/icon-extensions-power-unloaded.png \
            icons/icon-extensions-orientation-portait.png \
            icons/icon-extensions-orientation-landscape.png \
            icons/icon-extensions-orientation-auto.png \
            icons/icon-extensions-background-off.png \
            icons/icon-extensions-background-on.png \
            icons/icon-extensions-bluetooth-off.png \
            icons/icon-extensions-bluetooth-on.png \
            icons/icon-extensions-bluetooth-visible.png \
            icons/icon-extensions-brightness-max.png \
            icons/icon-extensions-brightness-med.png \
            icons/icon-extensions-brightness-min.png \
            icons/icon-extensions-cellular-2g.png \
            icons/icon-extensions-cellular-3g.png \
            icons/icon-extensions-cellular-dual.png \
            icons/icon-extensions-flashlight-off.png \
            icons/icon-extensions-flashlight-on.png \
            icons/icon-extensions-gsm-off.png \
            icons/icon-extensions-gsm-on.png \
            icons/icon-extensions-powersave-battery.png \
            icons/icon-extensions-powersave-off.png \
            icons/icon-extensions-powersave-on.png \
            icons/icon-extensions-powersave-auto.png \
            icons/icon-extensions-usb-ask.png \
            icons/icon-extensions-usb-mass.png \
            icons/icon-extensions-usb-sdk.png \
            icons/icon-extensions-usb-sync.png \
            icons/icon-extensions-usb-charging.png
png.path = /usr/share/themes/blanco/meegotouch/icons

dbus.files = org.coderus.glol.context
dbus.path = /usr/share/contextkit/providers

INSTALLS += target png dbus

HEADERS += \
    ApplicationExtensionController.h \
    ApplicationExtensionPlugin.h \
    AppletBrightness.h \
    AppletAvialability.h \
    AppletAvialabilityWidget.h \
    AppletTools.h \
    AppletToolsWidget.h \
    AppletToolsCellular.h \
    AppletToolsFlashlight.h \
    AppletToolsRadio.h \
    AppletToolsPowersave.h \
    AppletToolsBrightness.h \
    AppletToolsUsb.h \
    AppletToolsBackgroundconnections.h \
    AppletToolsBluetooth.h \
    AppletToolsOrientation.h \
    AppletToolsReboot.h

SOURCES += \
    ApplicationExtensionController.cpp \
    ApplicationExtensionPlugin.cpp \
    AppletBrightness.cpp \
    AppletAvialability.cpp \
    AppletAvialabilityWidget.cpp \
    AppletTools.cpp \
    AppletToolsWidget.cpp \
    AppletToolsCellular.cpp \
    AppletToolsFlashlight.cpp \
    AppletToolsRadio.cpp \
    AppletToolsPowersave.cpp \
    AppletToolsBrightness.cpp \
    AppletToolsUsb.cpp \
    AppletToolsBackgroundconnections.cpp \
    AppletToolsBluetooth.cpp \
    AppletToolsOrientation.cpp \
    AppletToolsReboot.cpp
