#ifndef APPLETTOOLSWIDGET_H
#define APPLETTOOLSWIDGET_H

#include <MImageWidget>
#include <gq/GConfItem>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <QGesture>
#include <MFlowLayoutPolicy>
#include <QEvent>
#include <QGestureEvent>
#include <MFeedback>

#include <TelepathyQt4/Account>

#include <QDBusConnection>
#include <QDBusInterface>

class AppletToolsWidget: public MImageWidget
{
public:
    explicit AppletToolsWidget(QString widget_name, bool using_longtap, QGraphicsObject *parent);
    void addIcon(QString iconId);
    void setIcon(int index);
    void setIndex(int index);
    int getIndex();
    void setStatus(bool status);
    bool getStatus();

protected:
    bool event(QEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    virtual void shortAction() = 0;
    virtual void longAction() = 0;

    GConfItem *m_key_status;
    GConfItem *m_key_index;

    MFeedback *feedback_press;
    MFeedback *feedback_release;
    MFeedback *feedback_long;

    QList<QString> m_icons;

    bool action;
};

#endif // APPLETTOOLSWIDGET_H
