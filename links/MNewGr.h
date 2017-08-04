#ifndef ORGANIZER_MNEWGR_H
#define ORGANIZER_MNEWGR_H

#include <mwgt.h>
#include <QtWidgets/QLineEdit>
#include "MLinksController.h"

class MWindow;

class MLinksController;

class MNewGr : public MTab {
	MWindow *wnd;
	MLinksController *contr;

	QLineEdit *name;

public:
	MNewGr(MWindow *w, MLinksController *c);

	void addClick();

	QString getDesc() override { return "New Tab"; }

	void importFrom(QString s) override {}

	QString exportTo() override { return ""; }

	void fromJson(QJsonValue v) override {}

	QJsonValue toJson() override { return QJsonValue(); }

	friend class MWindow;
};

#endif //ORGANIZER_MNEWGR_H
