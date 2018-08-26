/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <tabs/files/TFileGroup.h>
#include "tabs/editors/TEditor.h"
#include "tabs/links/TLinksGroup.h"
#include "tabs/TabsController.h"
#include <tabs/journals/TJournalTab.h>
#include <tabs/encrypted/TEncryptedTab.h>
#include <utils/logs/ULogger.h>

TabsController::TabsController(WMain *w) : wnd(w) {
//    sync = new NSync(this);
}

void TabsController::load() {
    logV("Loading tabs");

    QJsonArray docs = Storage::getInstance()->getDocs();

    logV("Tabs count: " + QString::number(docs.count()));

    tabs.fromJson(docs);
}

void TabsController::addNewTab(const QString &uuid, const QJsonObject &o) {
    auto w = tabs.addJson(uuid, o);
    QString name = o["name"].toString("Error");

    if (w != nullptr) { // if successfully created Tab
        int pos = wnd->tabs->count() - 1;
        wnd->tabs->insertTab(pos, w, name);
        wnd->tabs->setCurrentIndex(pos);
    }
}

void TabsController::save() {
    QJsonArray obj = tabs.toJsonA();

    Storage::getInstance()->setDocs(obj);
}

void TabsController::tabDel(const QString &uuid) {
    tabs.remove(uuid);
}

QList<Tab *> TabsController::selectByGroup(const QString &group) {
    QStringList keys;
    QList<Tab *> r;

    select_if(tabs, keys, [group](const QString &k) {
        return SGroups::getInstance()->isInGroup(group, k);
    });

    collect(keys, r, [this](const QString &k) { return tabs[k]; });

    return r;
}

void TabsController::swap(const QString &tab1, const QString &tab2) {
    tabs.swap(tab1, tab2);
}

void TabsController::recreate() {
    for (auto *tab : tabs.values())
        tab->deleteLater();

    tabs.clear();

    load();
}

void TabsController::lock() {
    for (Tab *tab : tabs.values()) {
        auto *t = dynamic_cast<TEncryptedTab *>(tab);

        if (t != nullptr) {
            t->lock();
        }
    }
}
