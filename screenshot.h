#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QObject>

class Screenshot : public QObject
{
    Q_OBJECT

public:
    explicit Screenshot(QObject* parent = nullptr);

    void shot();

signals:
    void ready(const QPixmap& image);
};

#endif // SCREENSHOT_H
