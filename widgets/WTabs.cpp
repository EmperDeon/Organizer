/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QMessageBox>
#include <tabs/TabNew.h>
#include <utils/logs/ULogger.h>

WTabs::WTabs(WMain *m) : main(m), contr(m->contr) {
    logD("Construction stared");
    groups = new WTGroups(this);

    connect(this, &QTabWidget::currentChanged, this, &WTabs::tabChange);
    connect(this->tabBar(), &QTabBar::tabMoved, this, &WTabs::tabMove); // FIXME: Moves wrong tabs if in group

    logD("Constructed");
}

void WTabs::tabNew() {
    if (newTab == nullptr && contr != nullptr && count() > 0) {
        newTab = new TabNew(main, contr);
        insertTab(count() - 1, newTab, "New Tab");
        setCurrentIndex(count() - 2);
        logV("Added NewTab");

    } else {
        setCurrentIndex(count() - 2);
    }
}

void WTabs::tabClose() {
    const QString &name = tabText(currentIndex()),
            &uuid = getCurrentTab()->uuid();

    if (uuid.isEmpty() || QMessageBox::question(this, QObject::tr("Close tab ?"), name) == QMessageBox::Yes) {
        contr->tabDel(uuid);
        removeTab(currentIndex());
        logV("Removed NewTab");
    }

    if (name == "New Tab")
        newTab = nullptr;
}

void WTabs::tabChange(int i) {
    if (i == (count() - 1)) {
        tabNew();
    }

    if (newTab != nullptr && newTab != getCurrentTab()) {
        for (int j = 0; j < count(); j++) {
            auto t = getTab(j);
            if (t && t->desc() == " ") {
                t->deleteLater(); // TODO: Delete newTab from TabBar, not itself
                logV("Removed NewTab");
            }
        }
        newTab = nullptr;
    }

    if (getCurrentTab() != nullptr) {
        getCurrentTab()->onSelected();
    }
}

void WTabs::cycleGroup() {
    groupBy(groups->nextGroup());
}

void WTabs::groupBy(QString group) {
    group = groups->setSelected(group);

    clear();

    for (Tab *t : contr->selectByGroup(group)) {
        addTab(t, t->name());
    }

    addTab(new QWidget, "+");
    setCurrentIndex(1);

    logD("Tabs regrouped");
}

void WTabs::setGroupsMenu(QMenu *menu) {
    groups->setMenu(menu);
}

void WTabs::tabMove(int from, int to) {
    Tab *t_from = getTab(from), *t_to = getTab(to);

    contr->swap(t_from->uuid(), t_to->uuid());
}
