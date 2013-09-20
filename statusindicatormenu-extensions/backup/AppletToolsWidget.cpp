#include "AppletToolsWidget.h"

AppletToolsWidget::AppletToolsWidget(QString widget_name, bool using_longtap, QGraphicsObject *parent):
    MImageWidget(parent)
{
    m_key_status = new GConfItem(QString("/apps/status-menu-extensions/tools/%1/working").arg(widget_name));
    m_key_index = new GConfItem(QString("/apps/status-menu-extensions/tools/%1/index").arg(widget_name));
    if (m_key_status->value().isNull())
        m_key_status->set(true);
    if (m_key_index->value().isNull())
    {
        if (widget_name == "bluetooth")
            m_key_index->set(0);
        else if (widget_name == "cellular")
            m_key_index->set(1);
        else if (widget_name == "flashlight")
            m_key_index->set(2);
        else if (widget_name == "radio")
            m_key_index->set(3);
        else if (widget_name == "powersave")
            m_key_index->set(4);
        else if (widget_name == "brightness")
            m_key_index->set(5);
        else if (widget_name == "usb")
            m_key_index->set(6);
        else if (widget_name == "bgconn")
            m_key_index->set(7);
        else if (widget_name == "orientation")
            m_key_index->set(8);
        else if (widget_name == "reboot")
            m_key_index->set(9);
    }

    setMaximumSize(64,64);
    setMinimumSize(64,64);
    setAspectRatioMode(Qt::KeepAspectRatio);

    feedback_press = new MFeedback("priority2_static_press", this);
    feedback_release = new MFeedback("priority2_static_release", this);
    feedback_long = new MFeedback("priority2_grab", this);

    if (using_longtap)
        grabGesture(Qt::TapAndHoldGesture);
}

void AppletToolsWidget::addIcon(QString iconId)
{
    m_icons.append(iconId);
}

void AppletToolsWidget::setIcon(int index)
{
    setImage(m_icons.at(index));
}

void AppletToolsWidget::setIndex(int index)
{
    m_key_index->set(index);
}

int AppletToolsWidget::getIndex()
{
    return m_key_index->value().toInt();
}

void AppletToolsWidget::setStatus(bool status)
{
    m_key_status->set(status);
}

bool AppletToolsWidget::getStatus()
{
    return m_key_status->value().toBool();
}

bool AppletToolsWidget::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture)
    {
        if (static_cast<QGestureEvent*>(event)->gesture(Qt::TapAndHoldGesture)->state() == Qt::GestureFinished && !action)
        {
            action = true;
            feedback_long->play();
            longAction();
        }
    }
    else
        return MImageWidget::event(event);
}

void AppletToolsWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    feedback_press->play();
    action = false;

    event->accept();
}

void AppletToolsWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (!action && contentsRect().contains(event->pos()))
    {
        action = true;
        feedback_release->play();
        shortAction();

        event->accept();
    }
}
