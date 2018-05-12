/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "WMain.h"
#include <QtWidgets/QApplication>
#include <QtGui/QHideEvent>
#include <QtWidgets/QInputDialog>
#include <widgets/sort/WTSorter.h>
#include <widgets/settings/WSettings.h>
#include <utils/logs/ULogger.h>


// Constructor
WMain::WMain() {
    logD("Construction started");

    w_sync = new WSync;
    tray = new UTray(this);

    contr = new MTabsController(this);
    tabs = new WTabs(this);

    contr->load();
    tabs->setMovable(true);

    constructMenuBar();

    tabs->groupBy();

    setCentralWidget(tabs);
    setGeometry(100, 100, 750, 500);

    logD("Constructed");
}

void WMain::constructMenuBar() {
    QMenuBar *menu = this->menuBar();

    QMenu *m_file = new QMenu("File");
    m_file->addAction("Settings", [=]() { (new WSettings)->show(); });
    m_file->addAction("Save", [=]() { contr->save(); }, QKeySequence::Save);
    m_file->addAction("Exit", this, &WMain::close, QKeySequence(Qt::CTRL + Qt::Key_Q));

    QMenu *m_tabs = new QMenu("Tabs");
    m_tabs->addAction("Add new tab", tabs, &WTabs::tabNew);
    m_tabs->addAction("Delete tab", tabs, &WTabs::tabClose);
    m_tabs->addAction("Manual sort of tabs", []() { WTSorter::sortTabs(); });

    QMenu *m_groups = new QMenu("Groups");
    tabs->setGroupsMenu(m_groups);

    QMenu *m_help = new QMenu("Help");
    m_help->addAction("About program");

    menu->addMenu(m_file);
    menu->addMenu(m_tabs);
    menu->addMenu(m_groups);
    menu->addMenu(m_help);

#ifdef OPTION_SYNC
    menu->addMenu(w_sync->getMenu());
#endif

    logD("Menu items created");
}
// Constructor


// Widget events
void WMain::closeEvent(QCloseEvent *e) {
    Q_UNUSED(e)

    logI("Closing application");

    contr->save();
    Storage::getInstance()->saveJson();
    tray->hide();
}

void WMain::hideEvent(QHideEvent *e) {
    hide();

    Storage::getInstance()->saveJson();
    e->accept();
}

void WMain::recreateTabs() {
    logI("Recreating tabs");

    tabs->clear();

    for (auto *tab : contr->tabs)
        tab->deleteLater();

    contr->tabs.clear();

    contr->load();
}
