/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <utils/Utils.h>
#include <QtGui/QtGui>
#include "SGroups.h"

SGroups::SGroups() {
    load();
}

bool SGroups::addTo(Tab *tab, QString group) {
    if (group == NO_GROUP || isInGroup(group, tab->uuid()))
        return false;

    if (group.isEmpty())
        group = current;

    // Remove from other
    for (const QString &o_group : groups.keys()) {
        groups[o_group]["notes"].eraseAllV(tab->uuid());
    }

    uuids << tab->uuid();
    groups[group]["notes"] += tab->uuid();

    return true;
}

bool SGroups::removeFromCurrent(Tab *tab, QString group) {
    if (group == NO_GROUP || !isInGroup(group, tab->uuid()))
        return false;

    if (group.isEmpty())
        group = current;

    uuids.removeAll(tab->uuid());
    groups[group]["notes"].eraseAllV(tab->uuid());

    return true;
}

void SGroups::create(const QString &name) {
    json_o obj = createGroupJson(name);
    groups.insert(name, obj);
}

void SGroups::removeCurrent() {
    for (QString uuid : groups[current]["notes"]) {
        uuids.removeAll(uuid);
    }

    groups.remove(current);
}

json_o SGroups::createGroupJson(const QString &name) {
    return {
            {"name",  name},
            {"notes", json_a()}
    };
}

QStringList SGroups::names() {
    return groups.keys();
}

bool SGroups::isInGroup(const QString &group, const QString &uuid) {
    if (uuid.isEmpty())
        return false;

    if (groups[group]["notes"].has_value(uuid))
        return true;

    return group == NO_GROUP && !uuids.contains(uuid);
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

    for (const json_o &k : groups) {
        for (QString uuid : groups[k]["notes"]) {
            uuids << uuid;
        }
    }
}

void SGroups::save() {
    Storage::getInstance()->set("groups", groups.toJson());
}
