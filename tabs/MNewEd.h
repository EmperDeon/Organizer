#ifndef ORGANIZER_MNEWED_H
#define ORGANIZER_MNEWED_H

#include <widgets/WMain.h>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include "MTabsController.h"

class WMain;

class MTabsController;

class MNewEd : public MTab {
    WMain *wnd;
	MTabsController *contr;

	QComboBox *type;
	QLineEdit *name;

public:
    MNewEd(WMain *w, MTabsController *c);

	QString getDesc() override { return "New Tab"; }

	void addClick();

    friend class WMain;
};

#endif //ORGANIZER_MNEWED_H
