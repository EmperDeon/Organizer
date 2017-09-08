#include <QtWidgets/QMessageBox>
#include <editors/MNewEd.h>
#include "WTabs.h"

WTabs::WTabs(WMain *m) : main(m), contr(main->contr) {
    tab_groups = {{"Editors", MTab::Editors},
                  {"Links",   MTab::Links},
                  {"Guides",  MTab::Guides}};

    connect(this, &QTabWidget::currentChanged, this, &WTabs::tabChange);

}

void WTabs::tabNew() {
    if (newTab == nullptr && contr != nullptr && count() > 0) {
        newTab = new MNewEd(main, contr);
        insertTab(count() - 1, newTab, "New Tab");
        setCurrentIndex(count() - 2);

    } else {
        setCurrentIndex(count() - 2);
    }
}

void WTabs::tabClose() {
    const QString &name = tabText(currentIndex());

    if (name == "New Tab" || QMessageBox::question(this, tr("Close tab ?"), name) == QMessageBox::Yes) {
        contr->tabDel(name);
        removeTab(currentIndex());
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
                t->deleteLater();
            }
        }
        newTab = nullptr;
    }
}

int WTabs::insertNewTab(int index, MTab *widget, const QString &string) {
    tabs << widget;

    return QTabWidget::insertTab(index, widget, string);
}

void WTabs::setAction(QAction *act) {
    this->action = act;
}

void WTabs::cycleGroup() {
    if (action != nullptr) {
        QString name;

        if (current_group == MTab::All) {
            name = "Editors";
        } else {
            name = findGroupName(current_group);
            name = findGroupAfter(name);
        }

        groupBy(tab_groups[name]);
    }
}

void WTabs::groupBy(MTab::TabGroup gr) {
    if (action != nullptr) {
        action->setText(findGroupName(gr));

        current_group = gr;

        // FIXME: Maybe causes memory leaks
        clear();

        for (MTab *t : contr->selectByGroup(gr)) {
            addTab(t, t->getName());
        }

        addTab(new QWidget, "+");
        setCurrentIndex(1);
    }
}

QString WTabs::findGroupName(MTab::TabGroup gr) {
    QString ret = "error";

    for (const QString &k : tab_groups.keys()) {
        if (tab_groups[k] == gr) {
            ret = k;
            break;
        }
    }

    return ret;
}

QString WTabs::findGroupAfter(QString name) {
    const QList<QString> &keys = tab_groups.keys();

    for (int i = 0; i < keys.size(); i++) {
        if (keys[i] == name) {
            if (i + 1 == keys.size()) { // Last key
                return keys.first();

            } else {
                return keys[i + 1];

            }
        }
    }

    return name;
}
