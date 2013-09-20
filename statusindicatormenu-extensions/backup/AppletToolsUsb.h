#ifndef APPLETTOOLSUSB_H
#define APPLETTOOLSUSB_H

#include "AppletToolsWidget.h"

class AppletToolsUsb: public AppletToolsWidget
{
    Q_OBJECT

public:
    explicit AppletToolsUsb(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    GConfItem *m_gconf_usb_mode;
    GConfItem *m_gconf_developer_mode;

private slots:
    void onValueChanged();
};

#endif // APPLETTOOLSUSB_H
