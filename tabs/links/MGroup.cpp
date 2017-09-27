#include <QtCore/QJsonArray>
#include <utils/UScrollArea.h>
#include "MGroup.h"

MGroup::MGroup(const QJsonObject &o) : MTab(o, MTab::LinksGroup), name(o["name"].toString()) {
	auto *scrollLayout = new QVBoxLayout;

	list = new QVBoxLayout;
	list->setAlignment(Qt::AlignTop);

	auto *scroll = new UScrollArea(list);

	scrollLayout->addWidget(scroll);
	scrollLayout->setMargin(0);

	setLayout(scrollLayout);

	load();
}

void MGroup::addLink(QJsonObject o) {
	MLink *link = new MLink(this, o);

	links << link;
	list->addWidget(link);
}

void MGroup::updateLinks() {
	if (!links.isEmpty() && !links.last()->isEmpty()) {
		addLink();
	}

	updated();
}

QString MGroup::getDesc() {
	return "Links group: " + name;
}

void MGroup::importFrom(QString s) {
	if (links.last()->isEmpty())
		links.last()->deleteLater(),
				links.removeLast();

	QString nm, ln;
	int i;
	for (QString l : s.split("\n")) { // TODO: Refactor
		if ((i = l.indexOf(": ")) != -1) {
			nm = QStringRef(&l, 0, i).toString();
			ln = QStringRef(&l, i + 2, l.size() - i - 2).toString();

		} else if ((i = l.indexOf(" - ")) != -1) {
			nm = QStringRef(&l, 0, i).toString();
			ln = QStringRef(&l, i + 3, l.size() - i - 3).toString();

		} else {
			ln = l;
		}

		QJsonObject o;
		o["name"] = nm;
		o["link"] = ln;
		addLink(o);
	}
}

QString MGroup::exportTo() { // TODO: Write export
	return nullptr;
}

void MGroup::fromJson(QJsonValue v) {
	QJsonArray arr = v.toArray();

	for (QJsonValue t : arr)
		addLink(t.toObject());

	if (arr.empty())
		addLink();

	for (MLink *l : links)
		l->editChange();
}

QJsonValue MGroup::toJson() {
	QJsonArray r;
	for (MLink *l : links) {
		if (!l->isEmpty())
			r << l->getJson();
	}

	return r;
}
