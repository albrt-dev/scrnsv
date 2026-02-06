#include "screenshot.h"

#include "overlay.h"

#include <QPixmap>
#include <QScreen>

Screenshot::Screenshot(QObject* parent)
    : QObject(parent)
{}

void Screenshot::shotAreaScreen()
{
    QScreen* screen = qApp->screens().at(0);

    Overlay* overlay = new Overlay(screen);
    connect(overlay, &Overlay::selected, this, [this, screen, overlay](const QRect& rect)
            { overlay->hide(); emit ready(screen->grabWindow(0, rect.x(), rect.y(), rect.width(), rect.height())); });
    overlay->show();
}

void Screenshot::shotFullScreen()
{
    QScreen* screen = qApp->screens().at(0);
    emit ready(screen->grabWindow(0));
}
