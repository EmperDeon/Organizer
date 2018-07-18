/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_SGROUPS_H
#define ORGANIZER_SGROUPS_H

#include <utils/USingleton.h>
#include <QtCore/QObject>
#include <tabs/Tab.h>
#include <storage/Storage.h>
#include "SMap.h"


class SGroups : public USingleton<SGroups> {
    SMap groups;
    QStringList uuids; // List all uuids, for NO_GROUP handling

    QString current;

    // This isn't really the best way - on language change this will be duplicated. But you can remove old group ?
    const QString NO_GROUP = QObject::tr("Other tabs");

public:
    SGroups();

    // Current group if empty string is passed
    bool addTo(Tab *tab, QString group = "");

    // Current group if empty string is passed
    bool removeFromCurrent(Tab *tab, QString group = "");

    void create(const QString &name);

    void removeCurrent();

    QJsonObject createGroupJson(const QString &name);

    QStringList names();

    bool isInGroup(const QString &group, Tab *tab);

    void setCurrent(const QString &group);

    QString nextGroup();

    void load();

    void save();
};


#endif //ORGANIZER_SGROUPS_H
