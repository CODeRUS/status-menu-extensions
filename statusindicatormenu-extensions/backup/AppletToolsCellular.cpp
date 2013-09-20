#include "AppletToolsCellular.h"

AppletToolsCellular::AppletToolsCellular(QGraphicsObject *parent):
    AppletToolsWidget("cellular", false, parent)
{
    addIcon("icon-extensions-cellular-2g");
    addIcon("icon-extensions-cellular-3g");
    addIcon("icon-extensions-cellular-dual");

    setIcon(2);

    m_radio = new Cellular::RadioAccess(this);
}

void AppletToolsCellular::enterDisplayEvent()
{
    connect(m_radio, SIGNAL(modeChanged(int)), this, SLOT(onModeChanged(int)));
    onModeChanged(m_radio->mode());
}

void AppletToolsCellular::exitDisplayEvent()
{
    disconnect(m_radio, SIGNAL(modeChanged(int)), this, SLOT(onModeChanged(int)));
}

void AppletToolsCellular::shortAction()
{
    switch (m_radio->mode())
    {
        case Cellular::RadioAccess::OnlyTwoG:
            m_radio->setMode(Cellular::RadioAccess::OnlyThreeG);
            break;
        case Cellular::RadioAccess::OnlyThreeG:
            m_radio->setMode(Cellular::RadioAccess::DualMode);
            break;
        default:
            m_radio->setMode(Cellular::RadioAccess::OnlyTwoG);
            break;
    }
}

void AppletToolsCellular::longAction()
{
}

void AppletToolsCellular::onModeChanged(int mode)
{
    switch (mode)
    {
        case Cellular::RadioAccess::OnlyTwoG:
            setIcon(0);
            break;
        case Cellular::RadioAccess::OnlyThreeG:
            setIcon(1);
            break;
        default:
            setIcon(2);
            break;
    }
}
