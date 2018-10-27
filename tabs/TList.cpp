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

void TList::fromJson(const json_o &obj) {
    QMap<QString, Tab *> map;

    if (obj.is_object()) {
        for (const auto &it : obj.items()) {
            map[QString::fromStdString(it.key())] = createNew(it.value());
        }

    } else if (obj.is_array()) {
        for (const auto &v : obj) {
            map[v["uuid"]] = createNew(obj);
        }
    }

    // TODO: Sync: Check contains(k) and compare last_updated

    addItems(map, [](Tab *o1, Tab *o2) {
        return o1->sortId() < o2->sortId();
    });
}

Tab *TList::addJson(const QString &key, const json_o &arr) {
    Tab *w = createNew(arr);

    if (w == nullptr) {
        return nullptr;
    }

    insert(key, w);

    return w;
}

json_o TList::toJson() {
    json_o o, t;

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

json_a TList::toJsonA() {
    json_a o;
    json_o t;

    for (int i = 0; i < m_keys.size(); i++) {
        const QString &k = m_keys[i];

        if (m_vals[k] == nullptr)
            continue;

        t = m_vals[k]->save();
        t["sort_id"] = i;
        o += t;
    }

    return o;
}

Tab *TList::createNew(const json_o &o, int i_type) {
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
