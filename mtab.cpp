#include <QtCore/QTimer>
#include <QtCore/QDateTime>
#include <storage/Storage.h>
#include "mtab.h"

MTab::MTab(const QJsonObject &o, TabType t) : obj(o), name(o["name"].toString()), type(t) {}

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

void MTab::load() {
	fromJson(obj["content"]);
}

QJsonObject MTab::save() {
	obj["content"] = toJson();
	obj["last_updated"] = u_last;
    obj["type"] = type;

	return obj;
}
