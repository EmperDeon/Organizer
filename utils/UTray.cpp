#include <QtWidgets/QtWidgets>
#include "UTray.h"

UTray::UTray(QMainWindow *w) : wnd(w), QSystemTrayIcon() {
    setIcon(qApp->windowIcon());

    auto *trayMenu = new QMenu;

    QAction *trayClick = new QAction("Toggle state");
    connect(trayClick, &QAction::triggered, this, &UTray::trayToggle);

    trayMenu->addAction(trayClick);
    setContextMenu(trayMenu);

    connect(this, &QSystemTrayIcon::activated, this, &UTray::trayClick);

    show();
}

void UTray::trayClick(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger) {
        trayToggle();
    }
}

void UTray::trayToggle() {
    if (!wnd->isVisible()) {
        if (wnd->isMinimized())
            wnd->showNormal();

        wnd->show();
        qApp->setActiveWindow(wnd);

    } else {
        wnd->hide();
    }
}
