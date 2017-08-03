#ifndef ORGANIZER_MNEWGR_H
#define ORGANIZER_MNEWGR_H

#include <mwgt.h>
#include <QtWidgets/QLineEdit>
#include "MLinksController.h"

class MWindow;

class MLinksController;

class MNewGr : public MTab {
Q_OBJECT

	MWindow *wnd;
	MLinksController *contr;

	QLineEdit *name;

public:
	MNewGr(MWindow *w, MLinksController *c);

	void addClick();

	QString getDesc() override { return "New Tab"; }

	void save() override {}

	void importFrom(QString s) override { Q_UNUSED(s) }

	QString exportTo() override { return ""; }

	friend class MWindow;
};

#endif //ORGANIZER_MNEWGR_H
