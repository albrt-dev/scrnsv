#include "screenshot.h"

#include <QPixmap>
#include <QScreen>

Screenshot::Screenshot(QObject* parent)
    : QObject(parent)
{}

void Screenshot::shot()
{
    QScreen* screen = qApp->screens().at(0);

    QPixmap image = screen->grabWindow(0);

    emit ready(image);
}
