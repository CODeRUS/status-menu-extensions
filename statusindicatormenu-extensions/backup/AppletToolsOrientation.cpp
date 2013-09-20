#include "AppletToolsOrientation.h"

#define DBUS_OBJECT "/org/maemo/contextkit/Screen/TopEdge"
#define DBUS_SERVICE "org.coderus.glol"

AppletToolsOrientation::AppletToolsOrientation(QGraphicsObject *parent):
    AppletToolsWidget("orientation", false, parent),
    m_currentstate(2),
    m_active(false)
{

    addIcon("icon-extensions-orientation-auto");
    addIcon("icon-extensions-orientation-landscape");
    addIcon("icon-extensions-orientation-portait");

    setIcon(0);
}

AppletToolsOrientation::~AppletToolsOrientation()
{
    QDBusConnection::sessionBus().unregisterObject(DBUS_OBJECT);
    QDBusConnection::sessionBus().unregisterService(DBUS_SERVICE);
}

void AppletToolsOrientation::enterDisplayEvent()
{
    if (!m_active)
    {
        QDBusConnection::sessionBus().registerObject(DBUS_OBJECT, this, QDBusConnection::ExportScriptableSignals|
                                                                        QDBusConnection::ExportScriptableSlots);
        QDBusConnection::sessionBus().registerService(DBUS_SERVICE);
        m_active = true;

        shortAction();
    }
}

void AppletToolsOrientation::shortAction()
{
    ++m_currentstate;

    switch (m_currentstate)
    {
    case 1:
        m_value = "top";
        m_timestamp = Q_INT64_C(-1);
        setIcon(1);
        break;
    case 2:
        m_value = "left";
        m_timestamp = Q_INT64_C(-1);
        setIcon(2);
        break;
    case 3:
        m_value = "auto";
        m_timestamp = 0;
        m_currentstate=0;
        setIcon(0);
        break;
    }

    emit ValueChanged(QVariantList() << m_value, m_timestamp);
}

void AppletToolsOrientation::longAction()
{
}

void AppletToolsOrientation::Subscribe(const QDBusMessage &msg, QVariantList &values, quint64 &timestamp)
{
    Q_UNUSED(msg);
    values << m_value;
    timestamp = m_timestamp;
}

void AppletToolsOrientation::Unsubscribe(const QDBusMessage &msg)
{
    Q_UNUSED(msg);
}
