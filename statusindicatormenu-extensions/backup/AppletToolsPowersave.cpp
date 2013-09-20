#include "AppletToolsPowersave.h"

AppletToolsPowersave::AppletToolsPowersave(QGraphicsObject *parent):
    AppletToolsWidget("powersave", true, parent)
{
    addIcon("icon-extensions-powersave-battery");
    setIcon(0);

    percentage = new MLabel(this);
    QFont font = percentage->font();
    font.setPixelSize(20);
    percentage->setColor(QColor(255,255,255));
    percentage->setPos(11,10);
    percentage->setVisible(true);

    m_gconf_autopsm = new GConfItem("/system/osso/dsm/energymanagement/enable_power_saving");
    m_gconf_forcepsm = new GConfItem("/system/osso/dsm/energymanagement/force_power_saving");
    m_battery = new MeeGo::QmBattery(this);
}

void AppletToolsPowersave::enterDisplayEvent()
{
    connect(m_gconf_autopsm, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));
    connect(m_gconf_forcepsm, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));
    onValueChanged();

    connect(m_battery, SIGNAL(batteryRemainingCapacityChanged(int,int)), this, SLOT(onBatteryChanged(int,int)));
    onBatteryChanged(m_battery->getRemainingCapacityPct(), 0);
}

void AppletToolsPowersave::exitDisplayEvent()
{
    disconnect(m_gconf_autopsm, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));
    disconnect(m_gconf_forcepsm, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));
    disconnect(m_battery, SIGNAL(batteryRemainingCapacityChanged(int,int)), this, SLOT(onBatteryChanged(int,int)));
}

void AppletToolsPowersave::shortAction()
{
    if (forcePSM)
    {
        m_gconf_forcepsm->set(false);
        m_gconf_autopsm->set(false);
    }
    else if (autoPSM)
    {
        m_gconf_forcepsm->set(true);
        m_gconf_autopsm->set(false);
    }
    else
    {
        m_gconf_forcepsm->set(false);
        m_gconf_autopsm->set(true);
    }
}

void AppletToolsPowersave::longAction()
{
    QDBusInterface("com.nokia.DuiControlPanel",
                   "/",
                   "com.nokia.DuiControlPanelIf",
                   QDBusConnection::sessionBus(),
                   this).call(QDBus::NoBlock,
                              "appletPage", "Battery");
}

void AppletToolsPowersave::onValueChanged()
{
    forcePSM = m_gconf_forcepsm->value().toBool();
    autoPSM = m_gconf_autopsm->value().toBool();

    if (forcePSM)
        percentage->setColor(QColor(60,200,255));
    else if (autoPSM)
        percentage->setColor(QColor(80,255,80));
    else
        percentage->setColor(QColor(255,255,255));
}

void AppletToolsPowersave::onBatteryChanged(int pct, int )
{
    if (pct < 100)
    {
        if (pct > 9)
            percentage->setText(QString("%1").arg(pct));
        else
            percentage->setText(QString("0%1").arg(pct));
    }
    else
    {
        percentage->setText(QString("##"));
    }
}
