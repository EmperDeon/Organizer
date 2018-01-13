/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_MEDITORS_H
#define ORGANIZER_MEDITORS_H

#include <storage/Storage.h>
#include <widgets/WMain.h>
#include <network/NSync.h>

class WMain;

class Storage;

class MTab;

class NSync;


class MTabsController : public QObject {
	WMain *wnd;
	NSync *sync;

public:
	QList<MTab *> tabs;

	explicit MTabsController(WMain *w);

	MTab *find(const QString &name);

	bool contains(const QString &name);

	void load();

	void save();

	void tabDel(QString name);

	~MTabsController() override = default;

	void addNewTab(const QString &name, const QJsonObject &o, int i = -1);

	QList<MTab *> selectByGroup(MTab::TabGroup gr);

	void move(int from, int to);
};


#endif //ORGANIZER_MEDITORS_H
