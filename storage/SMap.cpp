/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "SMap.h"

void SMap::fromJson(const json &obj) {
    QMap<QString, json> map;

    if (obj.is_object()) {
        for (const auto &it : obj.items()) {
            map[QString::fromStdString(it.key())] = it.value();
        }
    } else if (obj.is_array()) {
        for (const auto &v : obj) {
            map[v["name"]] = v;
        }
    }

    addItems(map, [](const json &o1, const json &o2) {
        int sort_one = o1["sort_id"], sort_two = o2["sort_id"];
        return sort_one < sort_two;
    });
}

json_o SMap::toJson() {
    json_o o;

    for (int i = 0; i < m_keys.size(); i++) {
        const QString &k = m_keys[i];

        o[k] = m_vals[k];
        o[k]["sort_id"] = i;
    }

    return o;
}

QString SMap::nextKey(const QString &key) {
    int index = m_keys.indexOf(key);

    if (index == -1 || index == (m_keys.size() - 1)) {
        return m_keys.first();
    } else {
        return m_keys[index + 1];
    }
}
