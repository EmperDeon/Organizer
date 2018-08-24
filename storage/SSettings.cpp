/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "SSettings.h"

SSettings::SSettings(Storage *stor) : storage(stor) {
    if (storage == nullptr) {
        storage = Storage::getInstance();
    }
}

json_o SSettings::object() {
    return storage->get("settings");
}

json SSettings::get(const QString &key) {
    json_o obj = object();

    if (!obj.contains(key)) {
        initializeDefaults();
        obj = object();
    }

    return obj[key];
}

bool SSettings::getB(const QString &key) {
    return get(key);
}

QString SSettings::getS(const QString &key) {
    return get(key);
}

int SSettings::getI(const QString &key) {
    return get(key);
}

void SSettings::set(const QString &key, const json &val) {
    json_o obj = object();
    obj[key] = val;
    storage->set("settings", obj)->saveJson();
}

json_a SSettings::allSettings() {
    QFile f(":/settings.json");
    f.open(QFile::ReadOnly);

    return json::parse(f.readAll().data());
}

void SSettings::initializeDefaults() {
//    qDebug() << "Settings key not found, initializingDefaults";

    json_o obj = object();

    for (const auto &level : allSettings()) {
        for (const json_o &entry : level["entries"]) {
            const QString &name = entry["name"];

            if (!obj.contains(name)) {
                obj[name] = entry["default"];
            }
        }
    }

    storage->set("settings", obj)->saveJson();
}
