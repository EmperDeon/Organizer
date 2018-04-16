/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QMessageBox>
#include <tabs/MNewTab.h>
#include <utils/logs/ULogger.h>

WTabs::WTabs(WMain *m) : main(m), contr(m->contr) {
    logD("Construction stared");
    groups = new WTGroups(this);

    connect(this, &QTabWidget::currentChanged, this, &WTabs::tabChange);
    connect(this->tabBar(), &QTabBar::tabMoved, contr, &MTabsController::move);

    logD("Constructed");
}

void WTabs::tabNew() {
    if (newTab == nullptr && contr != nullptr && count() > 0) {
        newTab = new MNewTab(main, contr);
        insertTab(count() - 1, newTab, "New Tab");
        setCurrentIndex(count() - 2);
        logV("Added MNewTab");

    } else {
        setCurrentIndex(count() - 2);
    }
}

void WTabs::tabClose() {
    const QString &name = tabText(currentIndex());

    if (name == "New Tab" || QMessageBox::question(this, QObject::tr("Close tab ?"), name) == QMessageBox::Yes) {
        contr->tabDel(name);
        removeTab(currentIndex());
        logV("Removed MNewTab");
    }

    if (name == "New Tab")
        newTab = nullptr;
}

void WTabs::tabChange(int i) {
    if (i == (count() - 1)) {
        tabNew();

    } else {
        MTab *t = getCurrentTab();
        if (t != nullptr)
            setWindowTitle(t->getDesc());
    }

    if (newTab != nullptr && newTab != getCurrentTab()) {
        for (int j = 0; j < count(); j++) {
            auto t = getTab(j);
            if (t && t->getDesc() == "New Tab") {
                t->deleteLater(); // TODO: Delete newTab from TabBar, not itself
                logV("Removed MNewTab");
            }
        }
        newTab = nullptr;
    }
}

void WTabs::cycleGroup() {
    groupBy(groups->findGroupAfterCurrent());
}

void WTabs::groupBy(QString group) {
    group = groups->setSelectedGroup(group);

    clear(); // FIXME: Maybe causes memory leaks

    for (MTab *t : contr->selectByGroup(group)) {
        addTab(t, t->getName());
    }

    addTab(new QWidget, "+");
    setCurrentIndex(1);
    logD("Tabs regrouped");
}

void WTabs::setGroupsMenu(QMenu *menu) {
    groups->setGroupsMenu(menu);
}
