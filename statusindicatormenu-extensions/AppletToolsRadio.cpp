#include "AppletToolsRadio.h"

AppletToolsRadio::AppletToolsRadio(QGraphicsObject *parent):
    AppletToolsWidget("radio", false, parent)
{
    addIcon("icon-extensions-gsm-off");
    addIcon("icon-extensions-gsm-on");

    setIcon(0);

    m_radio = new Cellular::SystemControl(this);
    connect(m_radio, SIGNAL(powerChanged(bool)), this, SLOT(onPowerChanged(bool)));
    onPowerChanged(m_radio->power());
}

void AppletToolsRadio::enterDisplayEvent()
{
}

void AppletToolsRadio::exitDisplayEvent()
{
}

void AppletToolsRadio::shortAction()
{
    m_radio->setPower(!m_radio->power());
}

void AppletToolsRadio::longAction()
{
}

void AppletToolsRadio::onPowerChanged(bool mode)
{
    if (mode)
        setIcon(1);
    else
        setIcon(0);
}
