#ifndef TRAYICON_H
#define TRAYICON_H

#include <QSystemTrayIcon>

class TrayIcon : public QObject
{
    Q_OBJECT

public:
    explicit TrayIcon(QObject* parent = nullptr);

    void show();
    void showMessage(const QString& title, const QString& text, const QPixmap& image);

signals:
    void screenshotRequested();
    void exitRequested();

private:
    void init();

    QSystemTrayIcon trayIcon_;
};

#endif // TRAYICON_H
