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

QJsonObject SSettings::object() {
    return storage->get("settings").toObject();
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

int SSettings::getI(const QString &key) {
    return get(key).toInt();
}

void SSettings::set(const QString &key, const QJsonValue &val) {
    QJsonObject obj = object();
    obj[key] = val;
    storage->set("settings", obj)->saveJson();
}

QJsonArray SSettings::allSettings() {
    QFile f(":/settings.json");
    f.open(QFile::ReadOnly);

    return Utils::fromJsonA(f.readAll());
}

void SSettings::initializeDefaults() {
//    qDebug() << "Settings key not found, initializingDefaults";

    QJsonObject obj = object();

    for (const auto &level : allSettings()) {
        for (const auto &t_entry : level.toObject()["entries"].toArray()) {
            const QJsonObject &entry = t_entry.toObject();
            const QString &name = entry["name"].toString();

            if (!obj.contains(name)) {
                obj[name] = entry["default"];
            }
        }
    }

    storage->set("settings", obj)->saveJson();
}
