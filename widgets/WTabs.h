/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_WTABWIDGET_H
#define ORGANIZER_WTABWIDGET_H

#include <QtWidgets/QTabWidget>
#include <tabs/MTab.h>
#include <tabs/MTabsController.h>
#include <widgets/groups/WTGroups.h>

class WMain;
class MTabsController;

class WTGroups;


class WTabs : public QTabWidget {
    WMain *main;
    MTabsController *contr;

    MTab *newTab = nullptr;

    WTGroups *groups;

public:
    explicit WTabs(WMain *m);

    void tabNew();

    void tabClose();

    void tabChange(int i);

    MTab *getTab(int i) { return dynamic_cast<MTab *>(widget(i)); }

    MTab *getCurrentTab() { return dynamic_cast<MTab *>(currentWidget()); }

    void cycleGroup();

    void groupBy(QString group = "");

    void setGroupsMenu(QMenu *menu);

    friend class WTGroups;
};


#endif //ORGANIZER_WTABWIDGET_H
