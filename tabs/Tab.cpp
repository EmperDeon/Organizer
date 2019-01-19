/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtCore/QTimer>
#include <QtCore/QDateTime>
#include <storage/Storage.h>
#include <utils/logs/ULogger.h>

Tab::Tab(const json_o &o, TabType t) {
	obj = o;
    t_name = obj["name"].get<QString>();
    t_uuid = obj["uuid"].get<QString>();
    t_sort_id = obj["sort_id"].get<int>();
	type = t;
    u_last = static_cast<qint64>(obj["last_updated"].get<double>());

    logV("Constructed Tab: " + desc());
}

void Tab::updated() {
	if (timer_not_started) {
		auto *u_timer = new QTimer();

        connect(u_timer, &QTimer::timeout, this, &Tab::saveStorage);

		u_last = QDateTime::currentMSecsSinceEpoch();
		u_timer->start(400);

		timer_not_started = false;
	}

	u_time = QDateTime::currentMSecsSinceEpoch();
}

void Tab::saveStorage() {
	if (u_time >= u_last && (u_time + 2000 < QDateTime::currentMSecsSinceEpoch())) {
		u_last = QDateTime::currentMSecsSinceEpoch();
		Storage::getInstance()->saveJson();
	}
}

const QString Tab::desc() {
    return tabTypeS(type) + " " + name();
}

void Tab::load(json_o o) {
//	qint64 n_last = static_cast<qint64>(o["last_updated"].toDouble());
//
//	if (n_last > u_last)

    logV("Loading JSON");

	if (o.empty()) {
		o = obj;
	}

    t_name = o["name"].get<QString>();
    t_uuid = o["uuid"].get<QString>();
    t_sort_id = o["sort_id"];
    u_last = static_cast<qint64>(o["last_updated"].get<double>());

	fromJson(o["content"]);
	loadCustomParams(o);
}

json_o Tab::save() {
    logV("Saving JSON");

	obj["content"] = toJson();
	obj["last_updated"] = u_last;
	obj["type"] = type;
    obj["sort_id"] = t_sort_id;

	saveCustomParams(obj);

    if (obj.contains(S_REPLACE_KEY)) {
        obj["content"] = obj[S_REPLACE_KEY];
        obj.erase(S_REPLACE_KEY);
    }

    if (obj.contains(S_DELETE_KEYS)) {
        obj.erase("password_hash");
        obj.erase("remember_me");
        obj.erase("remember_token");
        obj.erase("remember_until");
        obj.erase("tab_type");
        obj.erase(S_DELETE_KEYS);
    }

	return obj;
}

const QString Tab::tabTypeS(Tab::TabType type) {
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

void Tab::reloadJson(std::function<void(json &)> modifier) {
    json obj = toJson();
    modifier(obj);
    fromJson(obj);
}
