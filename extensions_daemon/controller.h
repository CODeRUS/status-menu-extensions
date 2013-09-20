#ifndef MYCLASS_H
#define MYCLASS_H

#include <gq/GConfItem>
#include <QObject>

#include <QtDBus/QtDBus>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusMessage>

#include <QDebug>

class DaemonController : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.coderus.daemon")

public:
    explicit DaemonController(QObject *parent = 0);

    void d_register();
    void d_unregister(int signal);

    bool registered;
    
public slots:
    Q_SCRIPTABLE void ping(bool isActive);
    Q_SCRIPTABLE void rebootDevice();
    Q_SCRIPTABLE void removeApplet(QString name);
    Q_SCRIPTABLE void restoreApplet(QString name);
    
};

#endif // MYCLASS_H
