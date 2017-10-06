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

class WMain;

class MTabsController;

class WTabs : public QTabWidget {
    WMain *main;
    MTabsController *contr;

    MTab *newTab = nullptr;

    // Groups cycle variables
    QAction *action = nullptr;
    MTab::TabGroup current_group = MTab::All;
    QMap<QString, MTab::TabGroup> tab_groups;

public:
    explicit WTabs(WMain *m);

    void tabNew();

    void tabClose();

    void tabChange(int i);

    MTab *getTab(int i) { return dynamic_cast<MTab *>(widget(i)); }

    MTab *getCurrentTab() { return dynamic_cast<MTab *>(currentWidget()); }

    void cycleGroup();

    void groupBy(MTab::TabGroup gr = MTab::All);

    void setAction(QAction *act);

    QString findGroupName(MTab::TabGroup gr);

    QString findGroupAfter(QString name);
};


#endif //ORGANIZER_WTABWIDGET_H
