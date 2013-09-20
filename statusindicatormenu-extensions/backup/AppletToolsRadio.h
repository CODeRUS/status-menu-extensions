#ifndef APPLETTOOLSRADIO_H
#define APPLETTOOLSRADIO_H

#include "AppletToolsWidget.h"
#include <CellularQt/SystemControl>

class AppletToolsRadio: public AppletToolsWidget
{
    Q_OBJECT

public:
    explicit AppletToolsRadio(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    Cellular::SystemControl *m_radio;

private slots:
    void onPowerChanged(bool mode);
};

#endif // APPLETTOOLSRADIO_H
