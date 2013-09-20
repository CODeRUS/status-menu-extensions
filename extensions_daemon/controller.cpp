#include <QFile>
#include <TelepathyQt4/Account>
#include <stdio.h>

#include "controller.h"

#define SYSTEM_OBJECT "/daemon"
#define SYSTEM_SERVICE "org.coderus.daemon"

DaemonController::DaemonController(QObject *parent) :
    QObject(parent)
{
}

void DaemonController::d_register()
{
    QDBusConnection::sessionBus().registerObject(SYSTEM_OBJECT, this, QDBusConnection::ExportScriptableSlots);
    registered = QDBusConnection::sessionBus().registerService(SYSTEM_SERVICE);

    if (registered)
        ping(true);
}

void DaemonController::d_unregister(int signal)
{
    GConfItem("/apps/status-menu-extensions/daemon_signal").set(signal);
    if (signal != -1)
        ping(false);

    QDBusConnection::sessionBus().unregisterService(SYSTEM_SERVICE);
    QDBusConnection::sessionBus().unregisterObject(SYSTEM_OBJECT);
}

void DaemonController::ping(bool isActive)
{
    QDBusInterface("com.nokia.systemui",
                   "/extensions/AppletToolsReboot",
                   "org.coderus.extensions",
                   QDBusConnection::sessionBus(),
                   0).call(QDBus::NoBlock,
                           "setDaemonStatus", isActive);
}

void DaemonController::rebootDevice()
{
    QDBusInterface("com.nokia.systemui",
                   "/",
                   "com.nokia.systemui.shutdownui",
                   QDBusConnection::sessionBus(),
                   this).call(QDBus::NoBlock,
                              "showScreen", "", "", 1);

    QDBusInterface("com.nokia.dsme",
                   "/com/nokia/dsme/request",
                   "com.nokia.dsme.request",
                   QDBusConnection::systemBus(),
                   this).call(QDBus::NoBlock,
                              "req_reboot");
}

void DaemonController::removeApplet(QString name)
{
    QString filename = QString("/usr/share/meegotouch/applicationextensions/statusindicatormenu-%1.desktop").arg(name);
    if (QFile(filename).exists())
        QFile(filename).remove();
}

void DaemonController::restoreApplet(QString name)
{
    QString template_path=QString("/usr/share/meegotouch/applicationextensions/statusindicatormenu-%1.desktop").arg(name);
    QString template_data=QString("\"[Desktop Entry]\nType=X-MeeGoApplicationExtension\nName=Status Indicator Menu Applet\n\n[X-MeeGoApplicationExtension]\nInterface=com.meego.core.MStatusIndicatorMenuExtensionInterface/1.0\nExtension=libstatusindicatormenu-%1.so\"").arg(name);
    system(QString("busybox echo %1 > %2").arg(template_data).arg(template_path).toAscii());
}
