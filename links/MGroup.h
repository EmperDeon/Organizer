#ifndef ORGANIZER_MGROUP_H
#define ORGANIZER_MGROUP_H

#include <mwgt.h>
#include <links/MLink.h>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QScrollArea>

class MTab;

class Storage;

class MLink;


class MGroup : public MTab {
	SDocument *cont;
	QJsonObject obj;
	QString name;

	QList<MLink *> links;

	QVBoxLayout *list;
	QScrollArea *scroll;


public:
	MGroup(SDocument *c, QJsonObject o);

	void addLink(QJsonObject o = QJsonObject());

	void updateLinks();

	QString getDesc() override;

	void save() override;

	void importFrom(QString s) override;

	QString exportTo() override;
};


#endif //ORGANIZER_MGROUP_H
