#include "screenshot.h"

#include "overlay.h"

#include <QPixmap>
#include <QScreen>

namespace
{
    QRect totalGeometry(const QList<QScreen*>& screens)
    {
        QRect total;

        for (QScreen* screen : screens)
        {
            if (screen)
                total = total.united(screen->geometry());
        }

        return total;
    }
}

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
    const QList<QScreen*> screens = qApp->screens();

    if (!screens.isEmpty())
    {
        const QRect area = totalGeometry(screens);
        emit ready(screens.at(0)->grabWindow(0, area.x(), area.y(), area.width(), area.height()));
    }
}
