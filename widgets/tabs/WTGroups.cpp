/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <tabs/MTab.h>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QInputDialog>
#include "WTGroups.h"

WTGroups::WTGroups(WTabs *t) : tabs(t), contr(t->contr) {

}

void WTGroups::addCurrentToGroup(const QString &group) {
    if (group == NO_GROUP)
        return;

    tabs->getCurrentTab()->addGroup(group);

    // FIXME: Remove tab from WTabs
}

void WTGroups::removeCurrentFromGroup() {
    tabs->getCurrentTab()->addGroup(current_group);

    // FIXME: Remove tab from WTabs
}

void WTGroups::createGroup(bool add_to) {
    QString name = QInputDialog::getText(tabs, QObject::tr("Creating tab group"), QObject::tr("Enter name: "));
    if (!name.isEmpty()) {
        l_groups.insert(l_groups.size() - 1, name);

        if (add_to)
            addCurrentToGroup(name);

        updateGroupsMenu();
    }
}

void WTGroups::deleteGroup() {
    if (!current_group.isEmpty()) {
        QString cur = current_group, mes = QObject::tr("Are you sure you want to delete tab group \"%1\" ?").arg(cur);

        if (QMessageBox::question(tabs, QObject::tr("Deleting tab group"), mes) == QMessageBox::Yes) {
            tabs->cycleGroup();

            l_groups.removeAll(cur);

            for (MTab *t : contr->tabs)
                t->removeGroup(cur);

            updateGroupsMenu();
        }
    }
}

void WTGroups::setGroupsMenu(QMenu *m) {
    m_groups = m;

    m_add = m_groups->addMenu(tr("Add current tab to: "));
    a_rem_from = m_groups->addAction("Remove from current group", [this]() { this->removeCurrentFromGroup(); });

    m_groups->addSeparator();

    m_goto = m_groups->addMenu(tr("Go to:"));
    m_groups->addAction(QObject::tr("Create new group"), this, &WTGroups::createGroup);
    a_del_group = m_groups->addAction("Delete current group", [this]() { this->deleteGroup(); });

    updateGroupsMenu();
}

void WTGroups::updateGroupsMenu() {
    if (l_groups.isEmpty())
        l_groups = groupNames();

    a_del_group->setDisabled(current_group == NO_GROUP);

    m_add->clear();

    m_add->addAction(QObject::tr("Add to new group"), [this]() { this->createGroup(true); });
    m_add->addSeparator();

    for (const QString &group : l_groups) {
        if (group == NO_GROUP)
            continue;

        auto *a = m_add->addAction(group, [this, group]() { this->addCurrentToGroup(group); });
        a->setDisabled(tabs->getCurrentTab()->isInGroup(group));
    }

    m_goto->clear();
    for (const QString &group : l_groups) {
        auto *a = m_goto->addAction(group, [this, group]() { this->tabs->groupBy(group); });
        a->setDisabled(group == current_group);
    }
}

QString WTGroups::setSelectedGroup(QString group) {
    if (l_groups.isEmpty())
        l_groups = groupNames();

    if (group.isEmpty()) // If default
        group = GROUP_SELECTED_IF_NULL(l_groups);

    current_group = group;

    updateGroupsMenu();

    // TODO: Change current in bottom ow window

    return group;
}

QString WTGroups::findGroupAfterCurrent() {
    int i = l_groups.indexOf(current_group);

    if (i == -1 || i == (l_groups.size() - 1)) {
        return l_groups.first();

    } else {
        return l_groups.value(i + 1);
    }
}

QStringList WTGroups::groupNames() {
    QStringList groups;

    for (MTab *t : contr->tabs) {
        for (const QString &group : t->groups())
            if (!groups.contains(group))
                groups << group;
    }

    groups << NO_GROUP;

    return groups;
}

