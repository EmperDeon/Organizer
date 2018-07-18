/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_WTGROUPS_H
#define ORGANIZER_WTGROUPS_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtWidgets/QMenu>
#include <widgets/WTabs.h>
#include <storage/SGroups.h>
#include <widgets/groups/WTGroupLabel.h>

class WTabs;

class TabsController;

class WTGroupLabel;


class WTGroups : public QObject {
    WTabs *tabs;
    TabsController *contr;

    SGroups *groups;
    QString current_group;

    WTGroupLabel *l_group;

    // Menu and actions
    QMenu *m_groups = nullptr, *m_add = nullptr, *m_goto = nullptr;
    QAction *a_del_group = nullptr;

    const QString NO_GROUP = QObject::tr("Other tabs");

public:
    explicit WTGroups(WTabs *t);

    void addCurrentTabTo(const QString &group);

    void removeFromCurrent();

    void create(bool add_to = false);

    void remove();

    void setMenu(QMenu *m);

    void updateMenu();


    QString setSelected(QString group);

    QString nextGroup();

    friend class WTGroupLabel;
};


#endif //ORGANIZER_WTGROUPS_H
