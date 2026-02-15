#ifndef OVERLAYWIDGET_H
#define OVERLAYWIDGET_H

#include <QWidget>

class OverlayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OverlayWidget(QWidget* parent = nullptr);

signals:
    void selected(const QRect& area);

protected:
    void paintEvent(QPaintEvent* event) override;

    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QRect area_;
};

#endif // OVERLAYWIDGET_H
