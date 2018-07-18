/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <utils/Utils.h>
#include <QtGui/QtGui>
#include "SGroups.h"

#define GROUPS_ARRAY_LOAD(group) QJsonArray notes = groups[(group)]["notes"].toArray()
#define GROUPS_ARRAY_SAVE(group) { QJsonObject obj = groups[(group)]; obj["notes"] = notes; groups[(group)] = obj; }

SGroups::SGroups() {
    load();
}

bool SGroups::addTo(Tab *tab, QString group) {
    if (group == NO_GROUP || isInGroup(group, tab) || tab->uuid().isEmpty())
        return false;

    if (group.isEmpty())
        group = current;

    GROUPS_ARRAY_LOAD(group);

    uuids << tab->uuid();
    notes.append(tab->uuid());

    GROUPS_ARRAY_SAVE(group);

    return true;
}

bool SGroups::removeFromCurrent(Tab *tab, QString group) {
    if (group == NO_GROUP || !isInGroup(group, tab))
        return false;

    if (group.isEmpty())
        group = current;

    GROUPS_ARRAY_LOAD(group);

    uuids.removeAll(tab->uuid());
    Utils::removeInArray(notes, tab->uuid());

    GROUPS_ARRAY_SAVE(group);

    return true;
}

void SGroups::create(const QString &name) {
    groups.insert(name, createGroupJson(name));
}

void SGroups::removeCurrent() {
    GROUPS_ARRAY_LOAD(current);

    for (const auto &uuid : notes) {
        uuids.removeAll(uuid.toString());
    }

    groups.remove(current);
}

QJsonObject SGroups::createGroupJson(const QString &name) {
    return {
            {"name",  name},
            {"notes", QJsonArray()}
    };
}

QStringList SGroups::names() {
    return groups.keys();
}

bool SGroups::isInGroup(const QString &group, Tab *tab) {
    GROUPS_ARRAY_LOAD(group);

    if (notes.contains(tab->uuid()))
        return true;

    return group == NO_GROUP && !uuids.contains(tab->uuid());
}

void SGroups::setCurrent(const QString &group) {
    current = group;
}

QString SGroups::nextGroup() {
    return groups.nextKey(current);
}

void SGroups::load() {
    groups = Storage::getInstance()->getMap("groups");

    if (!groups.contains(NO_GROUP)) {
        create(NO_GROUP);
    }

    for (const auto &k : groups) {
        for (const auto &uuid : groups[k]["notes"].toArray()) {
            uuids << uuid.toString();
        }
    }
}

void SGroups::save() {
    Storage::getInstance()->set("groups", groups.toJson());
}
