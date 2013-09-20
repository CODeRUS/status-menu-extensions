#include "AppletToolsUsb.h"

AppletToolsUsb::AppletToolsUsb(QGraphicsObject *parent):
    AppletToolsWidget("usb", false, parent)
{
    addIcon("icon-extensions-usb-ask");
    addIcon("icon-extensions-usb-sync");
    addIcon("icon-extensions-usb-mass");
    addIcon("icon-extensions-usb-charging");
    addIcon("icon-extensions-usb-sdk");

    setIcon(0);

    m_gconf_usb_mode = new GConfItem("/Meego/System/UsbMode");
    m_gconf_developer_mode = new GConfItem("/Meego/System/DeveloperMode");
}

void AppletToolsUsb::enterDisplayEvent()
{
    connect(m_gconf_usb_mode, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));
    onValueChanged();
}

void AppletToolsUsb::exitDisplayEvent()
{
    disconnect(m_gconf_usb_mode, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));
}

void AppletToolsUsb::shortAction()
{
    QString value = m_gconf_usb_mode->value().toString();

    if (value == "mass_storage")
        m_gconf_usb_mode->set("ovi_suite");
    else if (value == "ovi_suite")
    {
        if (m_gconf_developer_mode->value().toBool())
            m_gconf_usb_mode->set("windows_network");
        else
            m_gconf_usb_mode->set("charging_only");
    }
    else if (value == "windows_network")
        m_gconf_usb_mode->set("charging_only");
    else if (value == "charging_only")
        m_gconf_usb_mode->set("ask");
    else if (value == "ask")
        m_gconf_usb_mode->set("mass_storage");
}

void AppletToolsUsb::longAction()
{
}

void AppletToolsUsb::onValueChanged()
{
    QString value = m_gconf_usb_mode->value().toString();

    if (value == "mass_storage")
        setIcon(2);
    else if (value == "ovi_suite")
        setIcon(1);
    else if (value == "windows_network")
        setIcon(4);
    else if (value == "charging_only")
        setIcon(3);
    else if (value == "ask")
        setIcon(0);
}
