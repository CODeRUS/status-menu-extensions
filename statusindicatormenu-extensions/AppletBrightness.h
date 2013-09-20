#ifndef APPLETBRIGHTNESS_H
#define APPLETBRIGHTNESS_H

#include <MWidget>
#include <MImageWidget>

#include <MLabel>
#include <QGraphicsSceneMouseEvent>

#include <gq/GConfItem>
#include <QTime>

#include <QDBusConnection>

class AppletBrightness : public MWidget
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.coderus.extensions")

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *ev);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *ev);
    void enterDisplayEvent();
    void exitDisplayEvent();

public:
    explicit AppletBrightness(QGraphicsItem *parent = 0);
    virtual ~AppletBrightness();

private:
    MImageWidget *backgroundbar;
    MImageWidget *brightnessbar;
    MImageWidget *alpha0;
    GConfItem *m_gconf_brightness;

    GConfItem *m_bar_red;
    GConfItem *m_bar_green;
    GConfItem *m_bar_blue;

    void setBarWidthMove(int width);
    void setBarWidthPress(int width);

    QTime interval;
    QPixmap pix_brightnessbar;

private slots:
    void onValueChanged();

public slots:
    Q_SCRIPTABLE void setColor(int red, int green, int blue);

};

#endif // APPLETBRIGHTNESS_H
