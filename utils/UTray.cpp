/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QtWidgets>
#include "UTray.h"

UTray::UTray(QMainWindow *w) : QSystemTrayIcon(), wnd(w) {
    setIcon(qApp->windowIcon());

    auto *trayMenu = new QMenu;

    QAction *trayClick = new QAction("Toggle state", trayMenu);
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
