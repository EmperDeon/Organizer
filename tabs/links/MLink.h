#ifndef ORGANIZER_MLINK_H
#define ORGANIZER_MLINK_H

#include <QtCore/QJsonObject>
#include <QtWidgets/QLineEdit>
#include <tabs/links/MGroup.h>

class MGroup;


class MLink : public QWidget {
	MGroup *group;

	QLineEdit *l_name, *l_link;

	bool empty = true;

public:
	explicit MLink(MGroup *g, QJsonObject o = QJsonObject());

	bool isEmpty() const { return empty; }

	QJsonObject getJson() const;

	void editChange();

public:
	bool eventFilter(QObject *object, QEvent *event) override;
};


#endif //ORGANIZER_MLINK_H
