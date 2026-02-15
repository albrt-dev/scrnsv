#ifndef OVERLAY_H
#define OVERLAY_H

#include <QObject>

class QScreen;

class Overlay : public QObject
{
    Q_OBJECT

public:
    explicit Overlay(QObject* parent = nullptr);
    ~Overlay() override;

    void setScreens(const QList<QScreen*>& screens);

public slots:
    void show();
    void hide();

signals:
    void selected(QScreen* screen, const QRect& area);

private:
    QScopedPointer<class OverlayPrivate> d_;
};

#endif // OVERLAY_H
