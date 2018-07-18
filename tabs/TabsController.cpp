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

Tab *TabsController::find(const QString &name) {
    // std::find_if
    for (Tab *t : tabs) {
        if (t->name() == name)
            return t;
    }

    return nullptr;
}

bool TabsController::contains(const QString &name) {
    return find(name) != nullptr;
}

void TabsController::load() {
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

void TabsController::addNewTab(const QString &name, const QJsonObject &o, int i) {
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

Tab *TabsController::tabForType(const QJsonObject &o, int i_type) {
    Tab::TabType type;

    if (i_type == -1) {
        type = Tab::tabType(o);
    } else {
        type = Tab::tabType(i_type);
    }

    switch (type) {
        case Tab::Text:
            return new TEditor(o);

        case Tab::LinksGroup:
            return new TLinksGroup(o);

        case Tab::FilesGroup:
            return new TFileGroup(o);

        case Tab::Journal:
            return new TJournalTab(o);

        case Tab::Encrypted:
            return new TEncryptedTab(o);

        default:
            return nullptr;
    }
}

void TabsController::save() {
    QJsonArray obj;

    for (Tab *t : tabs) {
        if (t != nullptr)
            obj << t->save();
    }

    Storage::getInstance()->setDocs(obj);
}

void TabsController::tabDel(QString name) {
    tabs.removeAll(find(name));
}

QList<Tab *> TabsController::selectByGroup(const QString &group) {
    QList<Tab *> r;

    select_if(tabs, r, [group](Tab *t) {
        return SGroups::getInstance()->isInGroup(group, t);
    });

    return r;
}

void TabsController::move(int from, int to) {
    tabs.move(from, to);
}
