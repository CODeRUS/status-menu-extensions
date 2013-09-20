#ifndef APPLETTOOLSBACKGROUNDCONNECTIONS_H
#define APPLETTOOLSBACKGROUNDCONNECTIONS_H

#include "AppletToolsWidget.h"

class AppletToolsBackgroundconnections: public AppletToolsWidget
{
    Q_OBJECT

public:
    explicit AppletToolsBackgroundconnections(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    GConfItem *m_gconf_bgconn_mode;

private slots:
    void onValueChanged();
};

#endif // APPLETTOOLSBACKGROUNDCONNECTIONS_H
