/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_WTGROUPS_H
#define ORGANIZER_WTGROUPS_H

#include <QtCore/QObject>
#include <QtWidgets/QMenu>
#include <widgets/WTabs.h>
#include "WTGroupLabel.h"

class WTabs;

class TabsController;

class WTGroupLabel;

class WTGroups : public QObject {
    WTabs *tabs;
    TabsController *contr;

    QStringList l_groups;
    QString current_group = "";
    WTGroupLabel *l_group;

    const QString NO_GROUP = QObject::tr("Other tabs");

    // Menu and actions
    QMenu *m_groups = nullptr, *m_add = nullptr, *m_goto = nullptr;
    QAction *a_del_group = nullptr;

public:


    explicit WTGroups(WTabs *t);

    void addCurrentToGroup(const QString &group);

    void removeCurrentFromGroup();

    void createGroup(bool add_to = false);

    void deleteGroup();

    void setGroupsMenu(QMenu *m);

    void updateGroupsMenu();


    QString setSelectedGroup(QString group);

    QString findGroupAfterCurrent();

    QStringList groupNames();

    friend class WTGroupLabel;
};


#endif //ORGANIZER_WTGROUPS_H
