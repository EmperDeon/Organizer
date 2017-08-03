#ifndef ORGANIZER_MNEWED_H
#define ORGANIZER_MNEWED_H

#include <mwgt.h>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include "MEditorsController.h"

class MWindow;

class MEditorsController;

class MNewEd : public MTab {
Q_OBJECT

	MWindow *wnd;
	MEditorsController *contr;

	QComboBox *type;
	QLineEdit *name;

public:
	MNewEd(MWindow *w, MEditorsController *c);

	void addClick();

	QString getDesc() override { return "New Tab"; }

	void save() override {}

	void importFrom(QString s) override { Q_UNUSED(s) }

	QString exportTo() override { return ""; }

	~MNewEd() override = default;

	friend class MWindow;
};

#endif //ORGANIZER_MNEWED_H
