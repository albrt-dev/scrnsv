#include "screenshot.h"
#include "trayicon.h"

#include <QApplication>
#include <QClipboard>

void processScreenshot(const QPixmap& image)
{
    qApp->clipboard()->setPixmap(image);
    qApp->beep();
}

void showNotification(TrayIcon* const trayIcon, const QPixmap& image)
{
    trayIcon->showMessage("Screenshot has been copied to clipboard", "Paste screenshot wherever you want", image);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Screenshot screenshot;

    TrayIcon trayIcon;

    QObject::connect(&trayIcon, &TrayIcon::screenshotRequested, &screenshot, &Screenshot::shot);
    QObject::connect(&trayIcon, &TrayIcon::exitRequested, qApp, &QApplication::quit);

    QObject::connect(&screenshot, &Screenshot::ready, qApp,
                     [&trayIcon](const QPixmap& image) { processScreenshot(image); showNotification(&trayIcon, image); });

    trayIcon.show();

    return a.exec();
}
