#ifndef ORGANIZER_WMAIN_H
#define ORGANIZER_WMAIN_H

#include <storage/Storage.h>
#include <editors/MTab.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSystemTrayIcon>
#include <QtCore/QDateTime>
#include <QtCore/QTimer>
#include <widgets/WSync.h>
#include <editors/MTabsController.h>
#include "WTabs.h"


class Storage;

class MTab;

class MTabsController;

class WTabs;


class WMain : public QMainWindow {
    QAction *chAction;

    QSystemTrayIcon *tray;
    WSync *wsync;

public:
    WTabs *tabs;

    void importFrom();

    void exportTo();

    void trayClick(QSystemTrayIcon::ActivationReason reason);

    void trayToggle();

    MTabsController *contr = nullptr;
protected:
    void closeEvent(QCloseEvent *e) override;

    void hideEvent(QHideEvent *e) override;

public:
    WMain();

    void constructMenuBar();

    void changeWidget();

    // Singleton
    static WMain *getInstance() {
        static WMain *instance = nullptr;

        if (instance == nullptr) {
            instance = new WMain;
        }

        return instance;
    }

};


#endif //ORGANIZER_WMAIN_H
