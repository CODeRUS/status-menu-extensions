#include "ApplicationExtensionController.h"

#include <MImageWidget>

#define IC_OBJECT_NAME "/extensions/controller"

ApplicationExtensionsController::ApplicationExtensionsController(ApplicationExtensionsPlugin *extensionsPlugin,
                                                                 QGraphicsItem *parent) :
    MWidget(parent),
    m_extensionsPlugin(extensionsPlugin)
{
    QDBusConnection::sessionBus().registerObject(IC_OBJECT_NAME, this, QDBusConnection::ExportScriptableSlots);

    setObjectName("StatusIndicatorMenuExtensionContentItem");

    setMinimumHeight(0);

    m_layout = new MLayout(this);
    m_mainLayout = new MLinearLayoutPolicy(m_layout, Qt::Vertical);
    m_mainLayout->setContentsMargins(6, 0, 0, 0);

    a_brightness = new AppletBrightness(this);
    m_mainLayout->addItem(a_brightness);

    a_avialability = new AppletAvialability(this);
    m_mainLayout->addItem(a_avialability);
    s_avialability = new MWidget(this);
    s_avialability->setMinimumHeight(8);
    s_avialability->setMaximumHeight(8);
    m_mainLayout->addItem(s_avialability);

    s_tools_pre = new MWidget(this);
    s_tools_pre->setMinimumHeight(8);
    s_tools_pre->setMaximumHeight(8);
    m_mainLayout->addItem(s_tools_pre);
    a_tools = new AppletTools(this);
    m_mainLayout->addItem(a_tools);
    s_tools_aft = new MWidget(this);
    s_tools_aft->setMinimumHeight(8);
    s_tools_aft->setMaximumHeight(8);
    m_mainLayout->addItem(s_tools_aft);
}

ApplicationExtensionsController::~ApplicationExtensionsController()
{
    QDBusConnection::sessionBus().unregisterObject(IC_OBJECT_NAME);
}

void ApplicationExtensionsController::setItemVisibility(int index, bool isVisible)
{
    switch (index)
    {
    case 0:
        if (isVisible)
            m_mainLayout->insertItem(0, a_brightness);
        else
            m_mainLayout->removeItem(a_brightness);
        break;
    case 1:
        if (isVisible)
        {
            m_mainLayout->insertItem(m_mainLayout->indexOf(s_tools_pre), a_avialability);
            m_mainLayout->insertItem(m_mainLayout->indexOf(s_tools_pre), s_avialability);
        }
        else
        {
            m_mainLayout->removeItem(s_avialability);
            m_mainLayout->removeItem(a_avialability);
        }
        break;
    case 2:
        if (isVisible)
        {
            m_mainLayout->addItem(s_tools_pre);
            m_mainLayout->addItem(a_tools);
            m_mainLayout->addItem(s_tools_aft);
        }
        else
        {
            m_mainLayout->removeItem(s_tools_pre);
            m_mainLayout->removeItem(a_tools);
            m_mainLayout->removeItem(s_tools_aft);
        }
        break;
    }
}

