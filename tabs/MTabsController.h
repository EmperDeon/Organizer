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


class MTabsController {
	WMain *wnd;
	NSync *sync;

public:
	QMap<QString, MTab *> tabs;

	explicit MTabsController(WMain *w);

	void load();

	void save();

	void tabDel(QString name);

	~MTabsController() = default;

	void addNewTab(const QString &name, const QJsonObject &o, int i = -1);

	QList<MTab *> selectByGroup(MTab::TabGroup gr);
};


#endif //ORGANIZER_MEDITORS_H
