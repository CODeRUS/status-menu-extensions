#include "AppletTools.h"
#include <MImageWidget>

#define IT_OBJECT_NAME "/extensions/tools"

bool myLessThan(AppletToolsWidget *w1, AppletToolsWidget *w2)
{
    return w1->getIndex() < w2->getIndex();
}

AppletTools::AppletTools(QGraphicsItem *parent):
    MWidget(parent)
{
    QDBusConnection::sessionBus().registerObject(IT_OBJECT_NAME, this, QDBusConnection::ExportScriptableSlots);

    m_layout = new MLayout(this);

    m_mainLayout = new MFlowLayoutPolicy(m_layout);
    m_mainLayout->setContentsMargins(10,0,0,0);
    m_mainLayout->setSpacing(12);
    m_mainLayout->setVerticalSpacing(16);

    m_list.append(new AppletToolsBluetooth(0));
    m_list.append(new AppletToolsCellular(0));
    m_list.append(new AppletToolsFlashlight(0));
    m_list.append(new AppletToolsRadio(0));
    m_list.append(new AppletToolsPowersave(0));
    m_list.append(new AppletToolsBrightness(0));
    m_list.append(new AppletToolsUsb(0));
    m_list.append(new AppletToolsBackgroundconnections(0));
    m_list.append(new AppletToolsOrientation(0));
    m_list.append(new AppletToolsReboot(0));

    resort();

    push_index = -1;
}

AppletTools::~AppletTools()
{
    QDBusConnection::sessionBus().unregisterObject(IT_OBJECT_NAME);
}

void AppletTools::resort()
{
    qSort(m_list.begin(), m_list.end(), myLessThan);

    if (m_mainLayout->count() > 0)
    {
        for (int i = m_mainLayout->count() - 1; i != -1; i--)
        {
            m_mainLayout->removeAt(i);
        }
    }

    foreach (AppletToolsWidget *ww, m_list)
    {
        if (ww->getStatus())
        {
            m_mainLayout->addItem(ww);
        }
    }
}

void AppletTools::resetAll()
{
    GConfItem("/apps/status-menu-extensions/tools/bluetooth/index").set(0);
    GConfItem("/apps/status-menu-extensions/tools/cellular/index").set(1);
    GConfItem("/apps/status-menu-extensions/tools/flashlight/index").set(2);
    GConfItem("/apps/status-menu-extensions/tools/radio/index").set(3);
    GConfItem("/apps/status-menu-extensions/tools/powersame/index").set(4);
    GConfItem("/apps/status-menu-extensions/tools/brightness/index").set(5);
    GConfItem("/apps/status-menu-extensions/tools/usb/index").set(6);
    GConfItem("/apps/status-menu-extensions/tools/bgconn/index").set(7);
    GConfItem("/apps/status-menu-extensions/tools/orientation/index").set(8);
    GConfItem("/apps/status-menu-extensions/tools/reboot/index").set(9);

    GConfItem("/apps/status-menu-extensions/tools/bluetooth/working").set(true);
    GConfItem("/apps/status-menu-extensions/tools/cellular/working").set(true);
    GConfItem("/apps/status-menu-extensions/tools/flashlight/working").set(true);
    GConfItem("/apps/status-menu-extensions/tools/radio/working").set(true);
    GConfItem("/apps/status-menu-extensions/tools/powersame/working").set(true);
    GConfItem("/apps/status-menu-extensions/tools/brightness/working").set(true);
    GConfItem("/apps/status-menu-extensions/tools/usb/working").set(true);
    GConfItem("/apps/status-menu-extensions/tools/bgconn/working").set(true);
    GConfItem("/apps/status-menu-extensions/tools/orientation/working").set(true);
    GConfItem("/apps/status-menu-extensions/tools/reboot/working").set(true);
}

void AppletTools::setItemVisibility(int index, bool visible)
{
    m_list[index]->setStatus(visible);
    resort();
}

void AppletTools::swapItems(int index1, int index2)
{
    AppletToolsWidget *temp = m_list[index2];
    m_list[index2] = m_list[index1];
    m_list[index1] = temp;
    m_list[index1]->setIndex(index1);
    m_list[index2]->setIndex(index2);
    resort();
}

void AppletTools::pustIndexToSwap(int index)
{
    if (push_index != -1)
    {
        swapItems(index, push_index);
        push_index = -1;
    }
    else
        push_index = index;
}
