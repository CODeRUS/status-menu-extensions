#ifndef APPLETTOOLSCELLULAR_H
#define APPLETTOOLSCELLULAR_H

#include "AppletToolsWidget.h"
#include <CellularQt/RadioAccess>

class AppletToolsCellular: public AppletToolsWidget
{
    Q_OBJECT

public:
    explicit AppletToolsCellular(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    Cellular::RadioAccess *m_radio;

private slots:
    void onModeChanged(int mode);
};

#endif // APPLETTOOLSCELLULAR_H
