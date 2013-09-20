#include <QtCore/QCoreApplication>

#include <stdio.h>
#include <signal.h>

#include "controller.h"

DaemonController *controller;

static void handleSignal(int signal)
{
    printf(QString("Killed with signal: %1\n").arg(signal).toAscii());
    controller->d_unregister(signal);
    QCoreApplication::instance()->exit(0);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    signal(SIGINT,  handleSignal);
    signal(SIGHUP,  handleSignal);
    signal(SIGTERM, handleSignal);
    signal(SIGKILL, handleSignal);
    signal(SIGUSR1, handleSignal);
    signal(SIGUSR2, handleSignal);

    controller = new DaemonController();
    controller->d_register();

    if (controller->registered)
    {
        printf("Daemon successfully registered in session DBus\n");
        return a.exec();
    }
    else
    {
        printf("Can't register daemon in session DBus. Already running?\n");
        controller->d_unregister(-1);
        return 0;
    }
}
