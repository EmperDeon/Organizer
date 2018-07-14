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

class WMain;

class Storage;

class Tab;


class TabsController : public QObject {
	WMain *wnd;

public:
    QList<Tab *> tabs;

    explicit TabsController(WMain *w);

    Tab *find(const QString &name);

	bool contains(const QString &name);

	void load();

	void save();

	void tabDel(QString name);

	void addNewTab(const QString &name, const QJsonObject &o, int i = -1);

    QList<Tab *> selectByGroup(const QString &group);

	void move(int from, int to);

    static Tab *tabForType(const QJsonObject &o, int i_type = -1);
};


#endif //ORGANIZER_TABSCONTROLLER_H
