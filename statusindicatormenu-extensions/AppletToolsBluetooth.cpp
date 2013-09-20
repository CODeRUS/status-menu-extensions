#include "AppletToolsBluetooth.h"

AppletToolsBluetooth::AppletToolsBluetooth(QGraphicsObject *parent):
    AppletToolsWidget("bluetooth", true, parent)
{
    addIcon("icon-extensions-bluetooth-off");
    addIcon("icon-extensions-bluetooth-on");
    addIcon("icon-extensions-bluetooth-visible");

    setIcon(0);

    m_btLocalDevice = new QBluetoothLocalDevice(this);
}

void AppletToolsBluetooth::enterDisplayEvent()
{
    if (!m_btLocalDevice->isValid())
    {
        m_btLocalDevice = new QBluetoothLocalDevice(this);
        QBluetoothLocalDevice::HostMode mode = m_btLocalDevice->hostMode();
        m_btLocalDevice->powerOn();
        if (mode != QBluetoothLocalDevice::HostPoweredOff)
        {
            if (GConfItem("/system/osso/connectivity/BT/visible").value().toBool())
                m_btLocalDevice->setHostMode(QBluetoothLocalDevice::HostDiscoverable);
            else
                m_btLocalDevice->setHostMode(QBluetoothLocalDevice::HostConnectable);
        }
        else
            m_btLocalDevice->setHostMode(QBluetoothLocalDevice::HostPoweredOff);
        onBluetoothStateChanged(m_btLocalDevice->hostMode());
    }
    else
    {
        connect(m_btLocalDevice,
                SIGNAL(hostModeStateChanged(QBluetoothLocalDevice::HostMode)),
                this,
                SLOT(onBluetoothStateChanged(QBluetoothLocalDevice::HostMode)));
        onBluetoothStateChanged(m_btLocalDevice->hostMode());
    }
}

void AppletToolsBluetooth::exitDisplayEvent()
{
    disconnect(m_btLocalDevice,
               SIGNAL(hostModeStateChanged(QBluetoothLocalDevice::HostMode)),
               this,
               SLOT(onBluetoothStateChanged(QBluetoothLocalDevice::HostMode)));
}

void AppletToolsBluetooth::shortAction()
{
    switch (m_btLocalDevice->hostMode())
    {
    case QBluetoothLocalDevice::HostPoweredOff:
        m_btLocalDevice->powerOn();
        if (GConfItem("/system/osso/connectivity/BT/visible").value().toBool())
            m_btLocalDevice->setHostMode(QBluetoothLocalDevice::HostDiscoverable);
        else
            m_btLocalDevice->setHostMode(QBluetoothLocalDevice::HostConnectable);
        break;
    default:
        m_btLocalDevice->setHostMode(QBluetoothLocalDevice::HostPoweredOff);
        break;
    }
    onBluetoothStateChanged(m_btLocalDevice->hostMode());
}

void AppletToolsBluetooth::longAction()
{    
    QDBusInterface("com.nokia.DuiControlPanel",
                   "/",
                   "com.nokia.DuiControlPanelIf",
                   QDBusConnection::sessionBus(),
                   this).call(QDBus::NoBlock,
                              "appletPage", "Bluetooth");
}

void AppletToolsBluetooth::onBluetoothStateChanged(QBluetoothLocalDevice::HostMode mode)
{
    switch (mode)
    {
    case QBluetoothLocalDevice::HostPoweredOff:
        setIcon(0);
        break;
    case QBluetoothLocalDevice::HostConnectable:
        setIcon(1);
        break;
    default:
        setIcon(2);
        break;
    }
}

void AppletToolsBluetooth::onLongAction()
{
    QDBusInterface("com.nokia.DuiControlPanel",
                   "/",
                   "com.nokia.DuiControlPanelIf",
                   QDBusConnection::sessionBus(),
                   this).call("appletPage", "Bluetooth");
}
