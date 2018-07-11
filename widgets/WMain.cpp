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
#include <tabs/encrypted/TEncryptedTab.h>

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
    auto *a_sett = new QAction("Settings", m_file);
    QObject::connect(a_sett, &QAction::triggered, [=]() { (new WSettings)->show(); });
    m_file->addAction(a_sett);

    auto *a_lock = new QAction("Lock tabs", m_file);
    QObject::connect(a_lock, &QAction::triggered, [this]() { this->lockTabs(); });
    m_file->addAction(a_lock);

    auto *a_save = new QAction("Save", m_file);
    a_save->setShortcut(QKeySequence::Save);
    QObject::connect(a_save, &QAction::triggered, []() { Storage::getInstance()->saveJson(); });
    m_file->addAction(a_save);

    auto *a_exit = new QAction("Exit", m_file);
    a_exit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    QObject::connect(a_exit, &QAction::triggered, this, &WMain::close);
    m_file->addAction(a_exit);


    QMenu *m_tabs = new QMenu("Tabs");
    auto *a_tab_add = new QAction("Add new tab", m_tabs);
    QObject::connect(a_tab_add, &QAction::triggered, tabs, &WTabs::tabNew);
    m_tabs->addAction(a_tab_add);

    auto *a_tab_del = new QAction("Delete tab", m_tabs);
    QObject::connect(a_tab_del, &QAction::triggered, tabs, &WTabs::tabClose);
    m_tabs->addAction(a_tab_del);

    auto *a_tab_toggle = new QAction("Toggle tab encryption", m_tabs);
    QObject::connect(a_tab_toggle, &QAction::triggered,
                     [this]() { TEncryptedTab::toggleEncryption(this->tabs->getCurrentTab()); });
    m_tabs->addAction(a_tab_toggle);

    auto *a_tab_sort = new QAction("Manual sort of tabs", m_tabs);
    QObject::connect(a_tab_sort, &QAction::triggered, []() { WTSorter::sortTabs(); });
    m_tabs->addAction(a_tab_sort);

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

    tabs->groupBy();
}

void WMain::lockTabs() {
    for (MTab *tab : contr->tabs) {
        auto *t = dynamic_cast<TEncryptedTab *>(tab);

        if (t != nullptr) {
            t->lock();
        }
    }
}
