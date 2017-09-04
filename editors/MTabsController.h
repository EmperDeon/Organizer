#ifndef ORGANIZER_MEDITORS_H
#define ORGANIZER_MEDITORS_H

#include <storage/Storage.h>
#include <mwgt.h>
#include <network/NSync.h>

class MWindow;

class Storage;

class MTab;

class NSync;


class MTabsController {
	MWindow *wnd;
    QMap<QString, MTab *> tabs;
    NSync *sync;

public:
	explicit MTabsController(MWindow *w);

	void load();

	void save();

	MTab *addNew();

	void tabDel(QString name);

	~MTabsController() = default;

    void addNewTab(const QString &name, const QJsonObject &o, int i);
};


#endif //ORGANIZER_MEDITORS_H
