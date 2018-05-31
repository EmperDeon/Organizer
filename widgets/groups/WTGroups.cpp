/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <tabs/MTab.h>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QStatusBar>
#include "WTGroups.h"

WTGroups::WTGroups(WTabs *t) : tabs(t), contr(t->contr) {
    l_group = new WTGroupLabel(this);

    tabs->main->statusBar()->addPermanentWidget(l_group);
}

void WTGroups::addCurrentToGroup(const QString &group) {
    if (group == NO_GROUP || tabs->getCurrentTab()->isInGroup(group))
        return;

    tabs->getCurrentTab()->addGroup(group);

    tabs->removeTab(tabs->currentIndex());
}

void WTGroups::removeCurrentFromGroup() {
    if (current_group == NO_GROUP || !tabs->getCurrentTab()->isInGroup(current_group))
        return;

    tabs->getCurrentTab()->removeGroup(current_group);

    tabs->removeTab(tabs->currentIndex());
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
    auto *a_remove = new QAction("Remove from current group", m_groups);
    QObject::connect(a_remove, &QAction::triggered, [this]() { this->removeCurrentFromGroup(); });
    m_groups->addAction(a_remove);

    m_groups->addSeparator();

    m_goto = m_groups->addMenu(tr("Go to:"));
    auto *a_goto = new QAction(QObject::tr("Create new group"), m_groups);
    QObject::connect(a_goto, &QAction::triggered, this, &WTGroups::createGroup);
    m_groups->addAction(a_goto);

    a_del_group = new QAction("Delete current group", m_groups);
    QObject::connect(a_del_group, &QAction::triggered, [this]() { this->deleteGroup(); });
    m_groups->addAction(a_del_group);

    updateGroupsMenu();
}

void WTGroups::updateGroupsMenu() {
    if (l_groups.isEmpty())
        l_groups = groupNames();

    a_del_group->setDisabled(current_group == NO_GROUP);

    m_add->clear();

    auto *a_add = new QAction(QObject::tr("Add to new group"), m_add);
    QObject::connect(a_add, &QAction::triggered, [this]() { this->createGroup(true); });
    m_add->addAction(a_add);
    m_add->addSeparator();

    for (const QString &group : l_groups) {
        if (group == NO_GROUP)
            continue;

        auto *t_action = new QAction(group, m_add);
        QObject::connect(t_action, &QAction::triggered, [this, group]() { this->addCurrentToGroup(group); });
        m_add->addAction(t_action);
    }

    m_goto->clear();
    for (const QString &group : l_groups) {
        auto *a = new QAction(group, m_goto);
        QObject::connect(a, &QAction::triggered, [this, group]() { this->tabs->groupBy(group); });
        m_goto->addAction(a);
        a->setDisabled(group == current_group);
    }
}

QString WTGroups::setSelectedGroup(QString group) {
    if (l_groups.isEmpty())
        l_groups = groupNames();

    if (group.isEmpty()) // If default
        group = GROUP_SELECTED_IF_NULL(l_groups);

    current_group = group;

    l_group->setGroup(current_group);

    updateGroupsMenu();

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

