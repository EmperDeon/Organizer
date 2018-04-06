/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "SSettings.h"
#include "Storage.h"

QJsonObject SSettings::object() {
    return Storage::getInstance()->get("settings").toObject();
}

QJsonValue SSettings::get(const QString &key) {
    QJsonObject obj = object();

    if (!obj.contains(key)) {
        initializeDefaults();
        obj = object();
    }

    return obj[key];
}

bool SSettings::getB(const QString &key) {
    return get(key).toBool();
}

QString SSettings::getS(const QString &key) {
    return get(key).toString();
}

void SSettings::set(const QString &key, const QJsonValue &val) {
    QJsonObject obj = object();
    obj[key] = val;
    Storage::getInstance()->set("settings", obj)->saveJson();
}

QJsonArray SSettings::allSettings() {
    QFile f(":/settings.json");
    f.open(QFile::ReadOnly);

    return CTools::fromJsonA(f.readAll());
}

void SSettings::initializeDefaults() {
    QJsonObject obj = object();

    for (const auto &level : allSettings()) {
        for (const auto &t_entry : level.toObject()["entries"].toArray()) {
            const QJsonObject &entry = t_entry.toObject();
            const QString &name = entry["name"].toString();

            if (!obj.contains(name)) {
                obj[name] = obj["default"];
            }
        }
    }

    Storage::getInstance()->set("settings", obj)->saveJson();
}
