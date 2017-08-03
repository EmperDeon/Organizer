#ifndef ORGANIZER_MLINK_H
#define ORGANIZER_MLINK_H

#include <mwgt.h>
#include <links/MGroup.h>
#include <QtWidgets/QLineEdit>


class MGroup;

class MLink : public QWidget {
	MGroup *gr;

	QString name, link;
	QLineEdit *lN, *lL;

	bool empty = true;

public:
	explicit MLink(MGroup *g, QJsonObject o = QJsonObject());

	QString getName() const { return name; }

	QString getLink() const { return link; }

	bool isEmpty() const { return empty; }

	QJsonObject getJson() const;

	void editChange();

public:
	bool eventFilter(QObject *object, QEvent *event) override;
};


#endif //ORGANIZER_MLINK_H
