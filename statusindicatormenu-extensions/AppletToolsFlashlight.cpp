#include "AppletToolsFlashlight.h"

AppletToolsFlashlight::AppletToolsFlashlight(QGraphicsObject *parent):
    AppletToolsWidget("flashlight", false, parent)
{
    addIcon("icon-extensions-flashlight-off");
    addIcon("icon-extensions-flashlight-on");

    setIcon(0);

    fd = open("/dev/v4l-subdev10", O_RDWR | O_NONBLOCK, 0);
}

void AppletToolsFlashlight::enterDisplayEvent()
{
    if (!flashActive())
        setIcon(0);
    else
        setIcon(1);
}

void AppletToolsFlashlight::exitDisplayEvent()
{
}

void AppletToolsFlashlight::shortAction()
{
    if (!flashActive())
    {
        mode_ctrl.value = V4L2_FLASH_LED_MODE_TORCH;
        if (ioctl(fd, VIDIOC_S_CTRL, &mode_ctrl) != -1)
            setIcon(1);
    }
    else
    {
        mode_ctrl.value = V4L2_FLASH_LED_MODE_NONE;
        if (ioctl(fd, VIDIOC_S_CTRL, &mode_ctrl) != -1)
            setIcon(0);
    }
}

void AppletToolsFlashlight::longAction()
{
}

bool AppletToolsFlashlight::flashActive()
{
    if (fd == -1)
        fd = open("/dev/v4l-subdev10", O_RDWR | O_NONBLOCK, 0);

    if (fd != -1)
    {
        mode_ctrl.id = V4L2_CID_FLASH_LED_MODE;
        mode_ctrl.value = V4L2_FLASH_LED_MODE_NONE;
        ioctl(fd, VIDIOC_G_CTRL, &mode_ctrl);
        return (mode_ctrl.value != V4L2_FLASH_LED_MODE_NONE);
    }
    else
        return false;
}
