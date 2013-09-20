#ifndef APPLETTOOLSBRIGHTNESS_H
#define APPLETTOOLSBRIGHTNESS_H

#include "AppletToolsWidget.h"

class AppletToolsBrightness: public AppletToolsWidget
{
    Q_OBJECT

public:
    explicit AppletToolsBrightness(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    GConfItem *m_gconf_brightness;

private slots:
    void onValueChanged();
};

#endif // APPLETTOOLSBRIGHTNESS_H
