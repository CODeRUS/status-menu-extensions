#ifndef APPLETTOOLSREBOOT_H
#define APPLETTOOLSREBOOT_H

#include "AppletToolsWidget.h"
#include <QProcess>

class AppletToolsReboot: public AppletToolsWidget
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.coderus.extensions")

public:
    explicit AppletToolsReboot(QGraphicsObject *parent);
    virtual ~AppletToolsReboot();

    bool isDaemonActive;

protected:
    void enterDisplayEvent();

public slots:
    Q_SCRIPTABLE void setDaemonStatus(bool isActive);

private:
    void shortAction();
    void longAction();

    QProcess *daemon;

private slots:
    void startDaemon();
};

#endif // APPLETTOOLSREBOOT_H
