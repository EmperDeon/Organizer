/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtCore/QTimer>
#include <QtCore/QDateTime>
#include <storage/Storage.h>
#include <utils/logs/ULogger.h>
#include "MTab.h"

MTab::MTab(const QJsonObject &o, TabType t) {
	obj = o;
    t_name = obj["name"].toString();
	type = t;
	u_last = static_cast<qint64>(o["last_updated"].toDouble());

    logV("Constructed MTab: " + desc());
}

void MTab::updated() {
	if (timer_not_started) {
		auto *u_timer = new QTimer();

		connect(u_timer, &QTimer::timeout, this, &MTab::saveStorage);

		u_last = QDateTime::currentMSecsSinceEpoch();
		u_timer->start(400);

		timer_not_started = false;
	}

	u_time = QDateTime::currentMSecsSinceEpoch();
}

void MTab::saveStorage() {
	if (u_time >= u_last && (u_time + 2000 < QDateTime::currentMSecsSinceEpoch())) {
		u_last = QDateTime::currentMSecsSinceEpoch();
		Storage::getInstance()->saveJson();
	}
}

bool MTab::isInGroup(const QString &gr) {
	if (gr == NO_GROUP) {
		return t_groups.isEmpty();
	} else {
		return t_groups.contains(gr);
	}
}

void MTab::load(QJsonObject o) {
//	qint64 n_last = static_cast<qint64>(o["last_updated"].toDouble());
//
//	if (n_last > u_last)

    logV("Loading JSON");

	if (o.empty()) {
		o = obj;
	}

    t_name = o["name"].toString();
	u_last = static_cast<qint64>(o["last_updated"].toDouble());
	t_groups = CTools::arrayFromJson(o["groups"]);

	fromJson(o["content"]);
	loadCustomParams(o);
}

QJsonObject MTab::save() {
    logV("Saving JSON");

	obj["content"] = toJson();
	obj["last_updated"] = u_last;
	obj["type"] = type;
	obj["groups"] = CTools::arrayToJson(t_groups);

	saveCustomParams(obj);

    if (obj.contains(S_REPLACE_KEY)) {
        obj["content"] = obj[S_REPLACE_KEY];
        obj.remove(S_REPLACE_KEY);
    }

    if (obj.contains(S_DELETE_KEYS)) {
        obj.remove("password");
        obj.remove("password_hash");
        obj.remove("remember_me");
        obj.remove("tab_type");
        obj.remove(S_DELETE_KEYS);
    }

	return obj;
}

const QString MTab::tabTypeS(MTab::TabType type) {
    switch (type) {
        case Text:
            return QObject::tr("Text");
        case LinksGroup:
            return QObject::tr("Links");
        case FilesGroup:
            return QObject::tr("Files");
        case Journal:
            return QObject::tr("Journal");
        case Encrypted:
            return QObject::tr("Encrypted");
        default:
            break;
    }

    return QString();
}

const QString MTab::desc() {
    return tabTypeS(type) + " " + name();
}
