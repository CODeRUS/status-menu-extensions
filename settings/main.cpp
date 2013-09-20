#include <QDebug>

#include "settingsui.h"

#include <stdio.h>

#include <QtGui>
#include <MAction>
#include <MTheme>
#include <DcpWidget>
#include "main.h"
#include "brief.h"
#include "settingsui.h"

Q_EXPORT_PLUGIN2(statusmenuextennsionsapplet, StatusMenuExtensionsApplet)

void StatusMenuExtensionsApplet::init()
{

}

DcpWidget* StatusMenuExtensionsApplet::constructWidget(int widgetId)
{
    Q_UNUSED(widgetId);

    return pageMain();
}

DcpWidget* StatusMenuExtensionsApplet::pageMain()
{
    return new StatusMenuExtensionsWidget();
}



QString StatusMenuExtensionsApplet::title() const
{
    //% "Skeleton applet"
    return "Applet";
}

QVector<MAction*> StatusMenuExtensionsApplet::viewMenuItems()
{
    QVector<MAction*> vector(0);
    //% "Example action"
    //vector[0] = new MAction("NoAction", this);
    //vector[0]->setLocation(MAction::NoLocation);
    return vector;
}

DcpBrief* StatusMenuExtensionsApplet::constructBrief(int)
{
    return new StatusMenuExtensionsBrief();
}
