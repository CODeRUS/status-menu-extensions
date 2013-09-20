#include "ApplicationExtensionPlugin.h"
#include "ApplicationExtensionController.h"

Q_EXPORT_PLUGIN2(statusmenuextensions, ApplicationExtensionsPlugin)

ApplicationExtensionsPlugin::ApplicationExtensionsPlugin(QObject *parent) :
    statusIndicatorMenu(0),
    m_extensionsController(0)
{
    Q_UNUSED(parent)
}

void ApplicationExtensionsPlugin::setStatusIndicatorMenuInterface(MStatusIndicatorMenuInterface &menuInterface)
{
    statusIndicatorMenu = &menuInterface;
}

MStatusIndicatorMenuInterface *ApplicationExtensionsPlugin::statusIndicatorMenuInterface() const
{
    return statusIndicatorMenu;
}

bool ApplicationExtensionsPlugin::initialize(const QString &)
{
    m_extensionsController = new ApplicationExtensionsController(this);

    return true;
}

QGraphicsWidget *ApplicationExtensionsPlugin::widget()
{
    return m_extensionsController;
}
