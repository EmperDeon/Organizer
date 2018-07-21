/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_TABSCONTROLLER_H
#define ORGANIZER_TABSCONTROLLER_H

#include <storage/Storage.h>
#include <widgets/WMain.h>
#include <network/NSync.h>
#include "TList.h"

class WMain;

class Storage;

class Tab;


class TabsController : public QObject {
	WMain *wnd;
	TList tabs;

public:

    explicit TabsController(WMain *w);

	void load();

	void save();

	void tabDel(const QString &uuid);

	void addNewTab(const QString &uuid, const QJsonObject &o);

    QList<Tab *> selectByGroup(const QString &group);

	void swap(const QString &tab1, const QString &tab2);

	void recreate();

	void lock();
};


#endif //ORGANIZER_TABSCONTROLLER_H
