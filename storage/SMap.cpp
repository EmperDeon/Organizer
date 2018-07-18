/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "SMap.h"

void SMap::fromJson(const QJsonObject &obj) {
    QMap<QString, QJsonObject> map;

    for (const auto &k : obj.keys()) {
        map[k] = obj[k].toObject();
    }

    addItems(map, [](const QJsonObject &o1, const QJsonObject &o2) {
        return o1["sort_id"].toInt() < o2["sort_id"].toInt();
    });
}

void SMap::fromJson(const QJsonArray &arr) {
    QMap<QString, QJsonObject> map;

    for (const auto &v : arr) {
        auto obj = v.toObject();

        map[obj["name"].toString()] = obj;
    }

    addItems(map, [](const QJsonObject &o1, const QJsonObject &o2) {
        return o1["sort_id"].toInt() < o2["sort_id"].toInt();
    });
}

QJsonObject SMap::toJson() {
    QJsonObject o, t;

    for (int i = 0; i < m_keys.size(); i++) {
        const QString &k = m_keys[i];

        t = m_vals[k];
        t["sort_id"] = i;
        o[k] = t;
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
