/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <tabs/editors/TEditor.h>
#include <tabs/links/TLinksGroup.h>
#include <tabs/files/TFileGroup.h>
#include <tabs/journals/TJournalTab.h>
#include <tabs/encrypted/TEncryptedTab.h>
#include "TList.h"

void TList::fromJson(const QJsonObject &obj) {
    QMap<QString, Tab *> map;

    for (const auto &k : obj.keys()) {
        map[k] = createNew(obj[k].toObject());
    }

    // TODO: Sync: Check contains(k) and compare last_updated

    addItems(map, [](Tab *o1, Tab *o2) {
        return o1->sortId() < o2->sortId();
    });
}

void TList::fromJson(const QJsonArray &arr) {
    QMap<QString, Tab *> map;

    for (const auto &v : arr) {
        auto obj = v.toObject();

        map[obj["uuid"].toString()] = createNew(obj);
    }

    // TODO: Sync: Check contains(k) and compare last_updated

    addItems(map, [](Tab *o1, Tab *o2) {
        return o1->sortId() < o2->sortId();
    });
}

Tab *TList::addJson(const QString &key, const QJsonObject &arr) {
    Tab *w = createNew(arr);

    if (w == nullptr) {
        return nullptr;
    }

    insert(key, w);

    return w;
}

QJsonObject TList::toJson() {
    QJsonObject o, t;

    for (int i = 0; i < m_keys.size(); i++) {
        const QString &k = m_keys[i];

        if (m_vals[k] == nullptr)
            continue;

        t = m_vals[k]->save();
        t["sort_id"] = i;
        o[k] = t;
    }

    return o;
}

QJsonArray TList::toJsonA() {
    QJsonArray o;
    QJsonObject t;

    for (int i = 0; i < m_keys.size(); i++) {
        const QString &k = m_keys[i];

        if (m_vals[k] == nullptr)
            continue;

        t = m_vals[k]->save();
        t["sort_id"] = i;
        o << t;
    }

    return o;
}

Tab *TList::createNew(const QJsonObject &o, int i_type) {
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
