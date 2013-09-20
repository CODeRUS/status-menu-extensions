#ifndef APPLICATIONEXTENSIONCONTROLLER_H
#define APPLICATIONEXTENSIONCONTROLLER_H

#include <MWidget>
#include <MLayout>
#include <MLinearLayoutPolicy>

#include <QObject>
#include <QDBusConnection>

#include "ApplicationExtensionPlugin.h"
#include "AppletBrightness.h"
#include "AppletAvialability.h"
#include "AppletTools.h"

class MStatusIndicatorMenuInterface;

class ApplicationExtensionsController : public MWidget
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.coderus.extensions")

public:
    explicit ApplicationExtensionsController(ApplicationExtensionsPlugin *extensionsPlugin, QGraphicsItem *parent = NULL);
    virtual ~ApplicationExtensionsController();

public slots:
    Q_SCRIPTABLE void setItemVisibility(int index, bool isVisible);

private:
    MLayout *m_layout;
    MLinearLayoutPolicy *m_mainLayout;

    ApplicationExtensionsPlugin *m_extensionsPlugin;

    AppletBrightness *a_brightness;
    AppletAvialability *a_avialability;
    AppletTools *a_tools;

    MWidget *s_avialability;
    MWidget *s_tools_pre;
    MWidget *s_tools_aft;
};

#endif // APPLICATIONEXTENSIONCONTROLLER_H
