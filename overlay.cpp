#include "overlay.h"

#include "overlaywidget.h"

#include <QScreen>

class OverlayPrivate
{
public:
    OverlayPrivate(Overlay* qq) : q(qq) {}

    void show()
    {
        for (QScreen* screen : std::as_const(screens))
        {
            OverlayWidget* widget = new OverlayWidget();
            widget->setGeometry(screen->geometry());

            QObject::connect(widget, &OverlayWidget::selected, q, [this, screen](const QRect& area){ emit q->selected(screen, area); });

            widget->show();

            widgets.append(widget);
        }
    }

    void hide()
    {
        for (OverlayWidget* widget : std::as_const(widgets))
        {
            widget->hide();
            widget->deleteLater();
        }

        widgets.clear();
    }

    Overlay*              q;

    QList<QScreen*>       screens;
    QList<OverlayWidget*> widgets;
};

Overlay::Overlay(QObject* parent)
    : QObject(parent)
    , d_(new OverlayPrivate(this))
{}

Overlay::~Overlay() = default;

void Overlay::setScreens(const QList<QScreen*>& screens)
{
    d_->screens = screens;
}

void Overlay::show()
{
    d_->show();
}

void Overlay::hide()
{
    d_->hide();
}
