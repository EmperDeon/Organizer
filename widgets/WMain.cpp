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


// Constructor
WMain::WMain() {
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
}

void WMain::constructMenuBar() {
    QMenuBar *menu = this->menuBar();

    QMenu *m_file = new QMenu("File");
    m_file->addAction("Import", this, &WMain::importFrom);
    m_file->addAction("Export", this, &WMain::exportTo);
    m_file->addSeparator();
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
}
// Constructor


// Menu Slots
void WMain::importFrom() {
    bool ok;
    QString s = QInputDialog::getMultiLineText(this, "Enter text", "Text: ", "", &ok);

    if (ok)
        tabs->getCurrentTab()->importFrom(s);
}

void WMain::exportTo() {
    QInputDialog::getMultiLineText(this, "Exported text", "Text: ", tabs->getCurrentTab()->exportTo());
}
// Menu Slots


// Widget events
void WMain::closeEvent(QCloseEvent *e) {
    Q_UNUSED(e)

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
    tabs->clear();

    for (auto *tab : contr->tabs)
        tab->deleteLater();

    contr->tabs.clear();

    contr->load();
}
