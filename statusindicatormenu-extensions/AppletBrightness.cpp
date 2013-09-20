#include "AppletBrightness.h"

#include <MLocale>

#define IB_OBJECT_NAME "/extensions/brightness"

AppletBrightness::AppletBrightness(QGraphicsItem *parent):
    MWidget(parent)
{
    QDBusConnection::sessionBus().registerObject(IB_OBJECT_NAME, this, QDBusConnection::ExportScriptableSlots);

    MLocale locale;
    locale.installTrCatalog("settings");
    MLocale::setDefault(locale);

    setMaximumHeight(70);
    setMinimumHeight(70);

    MLabel *label = new MLabel(qtTrId("qtn_sett_main_brightness"), this);
    label->setColor(QColor(255,255,255));
    QFont font = label->font();
    font.setPixelSize(22);
    label->setFont(font);
    label->setPos(-5,-12);

    QPixmap *pix_background = new QPixmap(468,24);
    pix_background->fill(QColor(50,50,50));
    backgroundbar = new MImageWidget(pix_background, this);
    backgroundbar->setAspectRatioMode(Qt::IgnoreAspectRatio);
    backgroundbar->setGeometry(QRectF(0,26,468,24));

    m_bar_red = new GConfItem("/apps/status-menu-extensions/brightness/red");
    m_bar_green = new GConfItem("/apps/status-menu-extensions/brightness/green");
    m_bar_blue = new GConfItem("/apps/status-menu-extensions/brightness/blue");
    if (m_bar_red->value().isNull())
        m_bar_red->set(255);
    if (m_bar_green->value().isNull())
        m_bar_green->set(127);
    if (m_bar_blue->value().isNull())
        m_bar_blue->set(0);

    pix_brightnessbar = QPixmap(1,1);
    brightnessbar = new MImageWidget(&pix_brightnessbar, this);
    brightnessbar->setAspectRatioMode(Qt::IgnoreAspectRatio);
    brightnessbar->setMaximumHeight(24);
    brightnessbar->setMinimumHeight(24);
    brightnessbar->setMinimumWidth(0);
    brightnessbar->setMaximumWidth(468);
    brightnessbar->setPos(0,26);

    QImage *icon_background = new QImage("/usr/share/themes/blanco/meegotouch/icons/icon-extensions-background.png");
    MImageWidget *alpha1 = new MImageWidget(icon_background, this);
    alpha1->setPos(0,26);
    MImageWidget *alpha2 = new MImageWidget(icon_background, this);
    alpha2->setPos(467,26),
    alpha0 = new MImageWidget(icon_background, this);
    alpha0->setPos(-1,26);

    m_gconf_brightness = new GConfItem("/system/osso/dsm/display/display_brightness");
    onValueChanged();
}

AppletBrightness::~AppletBrightness()
{
    QDBusConnection::sessionBus().unregisterObject(IB_OBJECT_NAME);
}

void AppletBrightness::setBarWidthMove(int width)
{
    interval.restart();
    m_gconf_brightness->blockSignals(true);
    alpha0->setPos(-1,26);
    if (width < 50) {
        m_gconf_brightness->set(1);
        brightnessbar->setGeometry(QRectF(0,26,0,24));
    } else if ((width > 60) && (width < 97)) {
        m_gconf_brightness->set(2);
        brightnessbar->setGeometry(QRectF(0,26,117,24));
        alpha0->setPos(116,26);
    } else if ((width > 137) && (width < 214)) {
        m_gconf_brightness->set(3);
        brightnessbar->setGeometry(QRectF(0,26,234,24));
        alpha0->setPos(233,26);
    } else if ((width > 254) && (width < 331)) {
        m_gconf_brightness->set(4);
        brightnessbar->setGeometry(QRectF(0,26,351,24));
        alpha0->setPos(350,26);
    } else if (width > 371) {
        m_gconf_brightness->set(5);
        brightnessbar->setGeometry(QRectF(0,26,468,24));
    }

    m_gconf_brightness->blockSignals(false);
}

void AppletBrightness::setBarWidthPress(int width)
{
    m_gconf_brightness->blockSignals(true);
    alpha0->setPos(-1,26);
    if (width < 50) {
        m_gconf_brightness->set(1);
        brightnessbar->setGeometry(QRectF(0,26,0,24));
    } else if ((width > 49) && (width < 117)) {
        m_gconf_brightness->set(2);
        brightnessbar->setGeometry(QRectF(0,26,117,24));
        alpha0->setPos(116,26);
    } else if ((width > 116) && (width < 234)) {
        m_gconf_brightness->set(3);
        brightnessbar->setGeometry(QRectF(0,26,234,24));
        alpha0->setPos(233,26);
    } else if ((width > 233) && (width < 351)) {
        m_gconf_brightness->set(4);
        brightnessbar->setGeometry(QRectF(0,26,351,24));
        alpha0->setPos(350,26);
    } else if (width > 350) {
        m_gconf_brightness->set(5);
        brightnessbar->setGeometry(QRectF(0,26,468,24));
    }

    m_gconf_brightness->blockSignals(false);
}

void AppletBrightness::onValueChanged()
{
    int width = 470 * (m_gconf_brightness->value().toInt()-1) / 4;
    brightnessbar->setGeometry(QRectF(0,26,width,24));
    alpha0->setPos(width-1,26);
}

void AppletBrightness::setColor(int red, int green, int blue)
{
    pix_brightnessbar.fill(QColor(red, green, blue));
    brightnessbar->setPixmap(pix_brightnessbar);
}

void AppletBrightness::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    interval.start();
    setBarWidthMove(ev->pos().x());
}

void AppletBrightness::mouseMoveEvent(QGraphicsSceneMouseEvent *ev)
{
    if (interval.elapsed() > 100)
        setBarWidthMove(ev->pos().x());
}

void AppletBrightness::enterDisplayEvent()
{
    connect(m_gconf_brightness, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));
    onValueChanged();
    setColor(m_bar_red->value().toInt(),
             m_bar_green->value().toInt(),
             m_bar_blue->value().toInt());
}

void AppletBrightness::exitDisplayEvent()
{
    connect(m_gconf_brightness, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));
}

