#ifndef APPLETTOOLS_H
#define APPLETTOOLS_H

#include <MWidget>
#include <MImageWidget>
#include <QGraphicsWidget>
#include <MFlowLayoutPolicy>
#include <MLayout>
#include <QGraphicsSceneMouseEvent>
#include <QDBusConnection>
#include <gq/GConfItem>

#include "AppletToolsWidget.h"
#include "AppletToolsBluetooth.h"
#include "AppletToolsCellular.h"
#include "AppletToolsFlashlight.h"
#include "AppletToolsRadio.h"
#include "AppletToolsPowersave.h"
#include "AppletToolsBrightness.h"
#include "AppletToolsUsb.h"
#include "AppletToolsBackgroundconnections.h"
#include "AppletToolsOrientation.h"
#include "AppletToolsReboot.h"

class AppletTools : public MWidget
{

   Q_OBJECT
   Q_CLASSINFO("D-Bus Interface", "org.coderus.extensions")

public:
    explicit AppletTools(QGraphicsItem *parent = 0);
    virtual ~AppletTools();

private:
    MFlowLayoutPolicy *m_mainLayout;
    MLayout *m_layout;
    GConfItem *m_gconf_tools;
    QList<AppletToolsWidget*> m_list;
    int push_index;

    void resort();

public slots:
    Q_SCRIPTABLE void resetAll();
    Q_SCRIPTABLE void setItemVisibility(int index, bool visible);
    Q_SCRIPTABLE void swapItems(int index1, int index2);
    Q_SCRIPTABLE void pustIndexToSwap(int index);

};

#endif // APPLETTOOLS_H
