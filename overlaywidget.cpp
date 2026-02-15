#include "overlaywidget.h"

#include <QApplication>
#include <QMouseEvent>
#include <QPainter>

OverlayWidget::OverlayWidget(QWidget* parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);

    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);

    setWindowState(Qt::WindowFullScreen);
}

void OverlayWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    painter.fillRect(rect(), QColor(0, 0, 0, 127));

    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    painter.fillRect(area_.normalized(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

    painter.setPen(QPen(Qt::white, 1, Qt::DashLine));
    painter.drawRect(area_.normalized());
}

void OverlayWidget::showEvent(QShowEvent* event)
{
    qApp->setOverrideCursor(Qt::CrossCursor);
    qApp->overrideCursor();
}

void OverlayWidget::hideEvent(QHideEvent* event)
{
    qApp->restoreOverrideCursor();
    close();
}

void OverlayWidget::mousePressEvent(QMouseEvent* event)
{
    area_.setTopLeft(event->pos());
    area_.setBottomRight(event->pos());

    update();
}

void OverlayWidget::mouseMoveEvent(QMouseEvent* event)
{
    area_.setBottomRight(event->pos());

    update();
}

void OverlayWidget::mouseReleaseEvent(QMouseEvent* event)
{
    emit selected(area_.normalized());
}
