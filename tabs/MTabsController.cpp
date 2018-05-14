/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <tabs/files/MFlGroup.h>
#include "tabs/editors/MEdTab.h"
#include "tabs/links/MGroup.h"
#include "tabs/MTabsController.h"
#include <tabs/journals/TJournalTab.h>
#include <tabs/encrypted/TEncryptedTab.h>
#include <utils/logs/ULogger.h>

MTabsController::MTabsController(WMain *w) : wnd(w) {
//    sync = new NSync(this);
}

MTab *MTabsController::find(const QString &name) {
    // std::find_if
    for (MTab *t : tabs) {
        if (t->name() == name)
            return t;
    }

    return nullptr;
}

bool MTabsController::contains(const QString &name) {
    return find(name) != nullptr;
}

void MTabsController::load() {
    logV("Loading tabs");

    QJsonArray docs = Storage::getInstance()->getDocs();

    logV("Tabs count: " + QString::number(docs.count()));

    for (const auto &o : docs) {
        QJsonObject ob = o.toObject();
        QString name = ob["name"].toString("Error");

        if (contains(name)) {
            find(name)->load(ob);

        } else {
            addNewTab(name, ob);
        }
    }
}

void MTabsController::addNewTab(const QString &name, const QJsonObject &o, int i) {
    auto *w = tabForType(o);

    if (w != nullptr) {
        tabs << w;

        if (i == -1) {
            wnd->tabs->addTab(w, name);
        } else {
            wnd->tabs->insertTab(i, w, name);
        }
    }
}

MTab *MTabsController::tabForType(const QJsonObject &o, int i_type) {
    MTab::TabType type;

    if (i_type == -1) {
        type = MTab::tabType(o);
    } else {
        type = MTab::tabType(i_type);
    }

    switch (type) {
        case MTab::Text:
            return new MEdTab(o);

        case MTab::LinksGroup:
            return new MGroup(o);

        case MTab::FilesGroup:
            return new MFlGroup(o);

        case MTab::Journal:
            return new TJournalTab(o);

        case MTab::Encrypted:
            return new TEncryptedTab(o);

        default:
            return nullptr;
    }
}

void MTabsController::save() {
    QJsonArray obj;

    for (MTab *t : tabs) {
        if (t != nullptr)
            obj << t->save();
    }

    Storage::getInstance()->setDocs(obj);
}

void MTabsController::tabDel(QString name) {
    tabs.removeAll(find(name));
}

QList<MTab *> MTabsController::selectByGroup(const QString &group) {
    QList<MTab *> r;

    select_if(tabs, r, [group](MTab *t) {
        return t->isInGroup(group);
    });

    return r;
}

void MTabsController::move(int from, int to) {
    tabs.move(from, to);
}
