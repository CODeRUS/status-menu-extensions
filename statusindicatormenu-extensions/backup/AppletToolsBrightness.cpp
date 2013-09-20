#include "AppletToolsBrightness.h"

AppletToolsBrightness::AppletToolsBrightness(QGraphicsObject *parent):
    AppletToolsWidget("brightness", false, parent)
{
    addIcon("icon-extensions-brightness-min");
    addIcon("icon-extensions-brightness-med");
    addIcon("icon-extensions-brightness-max");

    setIcon(0);

    m_gconf_brightness = new GConfItem("/system/osso/dsm/display/display_brightness");
}

void AppletToolsBrightness::enterDisplayEvent()
{
    connect(m_gconf_brightness, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));
    onValueChanged();
}

void AppletToolsBrightness::exitDisplayEvent()
{
    disconnect(m_gconf_brightness, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));
}

void AppletToolsBrightness::shortAction()
{
    switch (m_gconf_brightness->value().toInt())
    {
    case 1: m_gconf_brightness->set(3);
            break;
    case 2:
    case 3:
    case 4: m_gconf_brightness->set(5);
            break;
    case 5: m_gconf_brightness->set(1);
            break;
    }
}

void AppletToolsBrightness::longAction()
{
}

void AppletToolsBrightness::onValueChanged()
{
    switch (m_gconf_brightness->value().toInt())
    {
    case 1: setIcon(0);
            break;
    case 2:
    case 3:
    case 4: setIcon(1);
            break;
    case 5: setIcon(2);
            break;
    }
}
