#ifndef ORGANIZER_MEDITORS_H
#define ORGANIZER_MEDITORS_H

#include <storage/Storage.h>
#include <mwgt.h>

class MWindow;

class Storage;

class MTab;


class MTabsController {
	MWindow *wnd;
	QList<MTab *> tabs;

public:
	QJsonArray *cont;

	explicit MTabsController(MWindow *w);

	void load();

	void save();

	MTab *addNew();

	void tabDel(QString name);

	~MTabsController() = default;

	void addNewTab(int i, const QJsonObject &o);
};


#endif //ORGANIZER_MEDITORS_H
