#include "trayicon.h"

#include <QMenu>

TrayIcon::TrayIcon(QObject *parent)
    : QObject(parent)
{
    init();
}

void TrayIcon::init()
{
    trayIcon_.setIcon(QIcon(":/icon.png"));

    QMenu* menu = new QMenu;

    menu->addAction("Make screenshot", QKeySequence(), this, &TrayIcon::screenshotRequested);
    menu->addAction("Quit", QKeySequence(), this, &TrayIcon::exitRequested);

    trayIcon_.setContextMenu(menu);
}

void TrayIcon::show()
{
    trayIcon_.setVisible(true);
    trayIcon_.show();
}

void TrayIcon::showMessage(const QString& title, const QString& text, const QPixmap& image)
{
    trayIcon_.showMessage(title, text, image);
}
