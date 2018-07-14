/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_WTABWIDGET_H
#define ORGANIZER_WTABWIDGET_H

#include <QtWidgets/QTabWidget>
#include <tabs/Tab.h>
#include <tabs/TabsController.h>
#include <widgets/groups/WTGroups.h>

class WMain;

class TabsController;

class WTGroups;


class WTabs : public QTabWidget {
    WMain *main;
    TabsController *contr;

    Tab *newTab = nullptr;

    WTGroups *groups;

public:
    explicit WTabs(WMain *m);

    void tabNew();

    void tabClose();

    void tabChange(int i);

    Tab *getTab(int i) { return dynamic_cast<Tab *>(widget(i)); }

    Tab *getCurrentTab() { return dynamic_cast<Tab *>(currentWidget()); }

    void cycleGroup();

    void groupBy(QString group = "");

    void setGroupsMenu(QMenu *menu);

    friend class WTGroups;
};


#endif //ORGANIZER_WTABWIDGET_H
