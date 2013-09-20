#include "AppletToolsReboot.h"

#define TR_OBJECT_NAME "/extensions/AppletToolsReboot"

AppletToolsReboot::AppletToolsReboot(QGraphicsObject *parent):
    AppletToolsWidget("reboot", true, parent)
{
    QDBusConnection::sessionBus().registerObject(TR_OBJECT_NAME, this, QDBusConnection::ExportScriptableSlots);

    addIcon("icon-extensions-power-unloaded");
    addIcon("icon-extensions-power");

    setIcon(0);

    isDaemonActive = false;
}

AppletToolsReboot::~AppletToolsReboot()
{
    QDBusConnection::sessionBus().unregisterObject(TR_OBJECT_NAME);
}

void AppletToolsReboot::enterDisplayEvent()
{
    if (!isDaemonActive)
    {
        system("/opt/status-menu-extensions/bin/extensions_daemon &");

        QDBusInterface("org.coderus.daemon",
                       "/daemon",
                       "org.coderus.daemon",
                       QDBusConnection::sessionBus(),
                       this).call(QDBus::NoBlock,
                                  "ping", true);
    }
}

void AppletToolsReboot::setDaemonStatus(bool isActive)
{
    if (isActive)
        setIcon(1);
    else
        setIcon(0);

    isDaemonActive = isActive;
}

void AppletToolsReboot::shortAction()
{
}

void AppletToolsReboot::longAction()
{
    if (isDaemonActive)
        QDBusInterface("org.coderus.daemon",
                       "/daemon",
                       "org.coderus.daemon",
                       QDBusConnection::sessionBus(),
                       this).call(QDBus::NoBlock,
                                  "rebootDevice");
}
