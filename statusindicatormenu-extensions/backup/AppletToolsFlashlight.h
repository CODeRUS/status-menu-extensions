#ifndef APPLETTOOLSFLASHLIGHT_H
#define APPLETTOOLSFLASHLIGHT_H

#include "AppletToolsWidget.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>

#define V4L2_CTRL_CLASS_FLASH           0x009c0000
#define V4L2_CID_FLASH_CLASS_BASE       (V4L2_CTRL_CLASS_FLASH | 0x900)
#define V4L2_CID_FLASH_TORCH_INTENSITY  (V4L2_CID_FLASH_CLASS_BASE + 8)
#define V4L2_CID_FLASH_LED_MODE         (V4L2_CID_FLASH_CLASS_BASE + 1)

enum v4l2_flash_led_mode {
    V4L2_FLASH_LED_MODE_NONE,
    V4L2_FLASH_LED_MODE_FLASH,
    V4L2_FLASH_LED_MODE_TORCH
};

class AppletToolsFlashlight: public AppletToolsWidget
{
    Q_OBJECT

public:
    explicit AppletToolsFlashlight(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    bool flashActive();

    int fd;
    v4l2_control mode_ctrl;
};

#endif // APPLETTOOLSFLASHLIGHT_H
