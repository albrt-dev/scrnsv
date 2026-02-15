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

    QPixmap screenImage(QScreen* screen, const QRect& rect)
    {
        QPixmap image;

        if (screen)
            image = screen->grabWindow(0, rect.x(), rect.y(), rect.width(), rect.height());

        return image;
    }

    QPixmap fullScreenImage(const QList<QScreen*>& screens)
    {
        QPixmap image;

        if (!screens.isEmpty())
        {
            const QRect area = totalGeometry(screens);

            // NOTE: Используем первый монитор, так как его достаточно, чтобы заскринить объединенную область мониторов
            image = screenImage(screens.at(0), area);
        }

        return image;
    }
}

Screenshot::Screenshot(QObject* parent)
    : QObject(parent)
{}

void Screenshot::shotAreaScreen()
{
    const QList<QScreen*> screens = qApp->screens();

    if (!screens.isEmpty())
    {
        Overlay* overlay = new Overlay;
        overlay->setScreens(screens);

        const auto grabArea = [this, overlay](QScreen* screen, const QRect& rect)
        {
            overlay->hide();

            const QPixmap image = screenImage(screen, rect);

            if (!image.isNull())
                emit ready(image);
        };

        connect(overlay, &Overlay::selected, this, grabArea);

        overlay->show();
    }
}

void Screenshot::shotFullScreen()
{
    const QPixmap image = fullScreenImage(qApp->screens());

    if (!image.isNull())
        emit ready(image);
}
