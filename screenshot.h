#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QObject>

class Screenshot : public QObject
{
    Q_OBJECT

public:
    explicit Screenshot(QObject* parent = nullptr);

    void shotAreaScreen();
    void shotFullScreen();

signals:
    void ready(const QPixmap& image);
};

#endif // SCREENSHOT_H
