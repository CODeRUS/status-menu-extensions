#ifndef APPLETTOOLSPOWERSAVE_H
#define APPLETTOOLSPOWERSAVE_H

#include "AppletToolsWidget.h"
#include <qmsystem2/qmbattery.h>
#include <QTimer>
#include <MLabel>

class AppletToolsPowersave: public AppletToolsWidget
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.coderus.extensions")

public:
    explicit AppletToolsPowersave(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    bool forcePSM;
    bool autoPSM;

    MLabel *percentage;

    GConfItem *m_gconf_autopsm;
    GConfItem *m_gconf_forcepsm;
    MeeGo::QmBattery *m_battery;

private slots:
    void onValueChanged();
    void onBatteryChanged(int pct, int);
};

#endif // APPLETTOOLSPOWERSAVE_H
