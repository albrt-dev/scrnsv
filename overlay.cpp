#include "overlay.h"

#include <QApplication>
#include <QMouseEvent>
#include <QPainter>

Overlay::Overlay(QScreen* screen)
    : QWidget(nullptr)
{    
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);

    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);

    setWindowState(Qt::WindowFullScreen);
}

void Overlay::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    painter.fillRect(rect(), QColor(0, 0, 0, 127));

    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    painter.fillRect(area_.normalized(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

    painter.setPen(QPen(Qt::white, 1, Qt::DashLine));
    painter.drawRect(area_.normalized());
}

void Overlay::showEvent(QShowEvent* event)
{
    qApp->setOverrideCursor(Qt::CrossCursor);
    qApp->overrideCursor();
}

void Overlay::hideEvent(QHideEvent* event)
{
    qApp->restoreOverrideCursor();
    close();
}

void Overlay::mousePressEvent(QMouseEvent* event)
{
    area_.setTopLeft(event->pos());
    area_.setBottomRight(event->pos());

    update();
}

void Overlay::mouseMoveEvent(QMouseEvent* event)
{
    area_.setBottomRight(event->pos());

    update();
}

void Overlay::mouseReleaseEvent(QMouseEvent* event)
{
    emit selected(area_.normalized());
}
