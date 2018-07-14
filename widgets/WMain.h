/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_WMAIN_H
#define ORGANIZER_WMAIN_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSystemTrayIcon>
#include <QtCore/QDateTime>
#include <QtCore/QTimer>
#include <utils/USingleton.h>
#include <utils/UTray.h>
#include "widgets/WSync.h"
#include "widgets/WTabs.h"
#include "tabs/TabsController.h"

class TabsController;

class WTabs;


class WMain : public QMainWindow, public USingleton<WMain> {
    WSync *w_sync;
    UTray *tray;

public:
    WTabs *tabs;

    TabsController *contr = nullptr;

protected:
    void closeEvent(QCloseEvent *e) override;

    void hideEvent(QHideEvent *e) override;

    void lockTabs();

public:
    WMain();

    void constructMenuBar();

    // Not just reload data "in tabs", but to reorder them [Called from WTSorter, TODO: Maybe make `reorder` method]
    void recreateTabs();
};


#endif //ORGANIZER_WMAIN_H
