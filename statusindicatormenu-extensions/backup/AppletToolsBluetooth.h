#ifndef APPLETTOOLSBLUETOOTH_H
#define APPLETTOOLSBLUETOOTH_H

#include "AppletToolsWidget.h"
#include <QBluetoothLocalDevice>

using namespace QtMobility;

class AppletToolsBluetooth: public AppletToolsWidget
{
    Q_OBJECT

public:
    explicit AppletToolsBluetooth(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    QBluetoothLocalDevice *m_btLocalDevice;

private slots:
    void onBluetoothStateChanged(QBluetoothLocalDevice::HostMode mode);
    void onLongAction();
};

#endif // APPLETTOOLSBLUETOOTH_H
