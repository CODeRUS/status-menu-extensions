#include "AppletToolsBackgroundconnections.h"

AppletToolsBackgroundconnections::AppletToolsBackgroundconnections(QGraphicsObject *parent):
    AppletToolsWidget("bgconn", false, parent)
{
    addIcon("icon-extensions-background-off");
    addIcon("icon-extensions-background-on");

    setIcon(1);

    m_gconf_bgconn_mode = new GConfItem("/system/osso/connectivity/network_type/restricted_mode");
    connect(m_gconf_bgconn_mode, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));
    onValueChanged();
}

void AppletToolsBackgroundconnections::enterDisplayEvent()
{
}

void AppletToolsBackgroundconnections::exitDisplayEvent()
{
}

void AppletToolsBackgroundconnections::shortAction()
{
    m_gconf_bgconn_mode->set(!m_gconf_bgconn_mode->value().toBool());
}

void AppletToolsBackgroundconnections::longAction()
{
}

void AppletToolsBackgroundconnections::onValueChanged()
{
    if (m_gconf_bgconn_mode->value().toBool())
        setIcon(0);
    else
        setIcon(1);
}
