#include <QApplication>
#include <QClipboard>
#include <QMenu>
#include <QScreen>
#include <QSystemTrayIcon>

void screenShot()
{
    QScreen* screen = qApp->screens().at(0);
    QPixmap image = screen->grabWindow(0);

    QApplication::beep();

    qApp->clipboard()->setPixmap(image);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSystemTrayIcon trayIcon;
    trayIcon.setIcon(QIcon(":/icon.png"));

    QMenu menu;

    QAction screenShotAction("Screenshot");
    QObject::connect(&screenShotAction, &QAction::triggered, &screenShotAction, [](){ screenShot(); });

    menu.addAction(&screenShotAction);

    QAction exitAction("Exit");
    QObject::connect(&exitAction, &QAction::triggered, &exitAction, [](){ qApp->exit(); });

    menu.addAction(&exitAction);

    trayIcon.setContextMenu(&menu);

    trayIcon.setVisible(true);
    trayIcon.show();

    return a.exec();
}
