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
#include <QDebug>

MTabsController::MTabsController(WMain *w) : wnd(w) {
    sync = new NSync(this);
}

MTab *MTabsController::find(const QString &name) {
    for (MTab *t : tabs) {
        if (t->getName() == name)
            return t;
    }

    return nullptr;
}

bool MTabsController::contains(const QString &name) {
    return find(name) != nullptr;
}

void MTabsController::load() {
    QJsonArray docs = Storage::getInstance()->getDocs();

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
    MTab *w;

    MTab::TabType type = static_cast<MTab::TabType>(o["type"].toInt(100));

    switch (type) {
        case MTab::Text:
            w = new MEdTab(o);
            break;
        case MTab::LinksGroup:
            w = new MGroup(o);
            break;
        case MTab::FilesGroup:
            w = new MFlGroup(o);
            break;
        case MTab::Journal:
            w = new TJournalTab(o);
            break;

        default:
            w = nullptr;
            break;
    }

    if (w != nullptr) {
        wnd->tabs->addTab(w, name);
        tabs << w;

        if (i != -1) {
            wnd->tabs->insertTab(i, w, name);
        }
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

QList<MTab *> MTabsController::selectByGroup(MTab::TabGroup gr) {
    auto r = QList<MTab *>();

    for (MTab *n : tabs) {
        if (n->isInGroup(gr)) {
            r << n;
        }
    }

    return r;
}

void MTabsController::move(int from, int to) {
    tabs.move(from, to);
}
