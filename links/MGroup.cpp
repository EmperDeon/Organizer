#include <QtCore/QJsonArray>
#include "MGroup.h"

MGroup::MGroup(SDocument *c, QJsonObject o) : cont(c), obj(o), name(o["name"].toString()) {
	scroll = new QScrollArea;
	auto *scrollLayout = new QVBoxLayout;
	QWidget *w = new QWidget;

	list = new QVBoxLayout;

	QJsonArray arr = obj["links"].toArray();

	for (QJsonValue v : arr)
		addLink(v.toObject());

	if (arr.empty())
		addLink();

	for (MLink *l : links)
		l->editChange();

	list->setAlignment(Qt::AlignTop);
	w->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	w->setLayout(list);

	scroll->setWidget(w);
	scroll->setWidgetResizable(true);
	scroll->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
	scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scroll->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);

	scrollLayout->addWidget(scroll);
	scrollLayout->setMargin(0);

	setLayout(scrollLayout);
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

void MGroup::save() {
	QJsonArray a;
	for (MLink *l : links) {
		if (!l->isEmpty())
			a << l->getJson();
	}
	obj["links"] = a;

	cont->insert(name, obj);
}

void MGroup::importFrom(QString s) {
	if (links.last()->isEmpty())
		links.last()->deleteLater(),
				links.removeLast();

	QString nm, ln;
	int i;
	for (QString l : s.split("\n")) {
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

QString MGroup::exportTo() {
	return nullptr;
}
