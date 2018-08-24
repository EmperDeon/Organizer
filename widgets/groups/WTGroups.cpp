/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <tabs/Tab.h>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QStatusBar>
#include "WTGroups.h"

WTGroups::WTGroups(WTabs *t) : tabs(t), contr(t->contr) {
    groups = SGroups::getInstance();
    l_group = new WTGroupLabel(this);

    tabs->main->statusBar()->addPermanentWidget(l_group);
}

void WTGroups::addCurrentTabTo(const QString &group) {
    if (groups->addTo(tabs->getCurrentTab(), group))
        tabs->removeTab(tabs->currentIndex());
}

void WTGroups::removeFromCurrent() {
    if (groups->removeFromCurrent(tabs->getCurrentTab()))
        tabs->removeTab(tabs->currentIndex());
}

void WTGroups::create(bool add_to) {
    QString name = QInputDialog::getText(tabs, QObject::tr("Creating tab group"), QObject::tr("Enter name: "));
    if (!name.isEmpty()) {
        groups->create(name);

        if (add_to)
            addCurrentTabTo(name);

        updateMenu();
    }
}

void WTGroups::remove() {
    if (!current_group.isEmpty()) {
        QString cur = current_group, mes = QObject::tr("Are you sure you want to delete tab group \"%1\" ?").arg(cur);

        if (QMessageBox::question(tabs, QObject::tr("Deleting tab group"), mes) == QMessageBox::Yes) {
            QString next_key = nextGroup();

            groups->removeCurrent();

            tabs->groupBy(next_key);

            updateMenu();
        }
    }
}

void WTGroups::setMenu(QMenu *m) {
    m_groups = m;

    m_add = m_groups->addMenu(tr("Add current tab to: "));
    auto *a_remove = new QAction("Remove from current group", m_groups);
    QObject::connect(a_remove, &QAction::triggered, [this]() { this->removeFromCurrent(); });
    m_groups->addAction(a_remove);

    m_groups->addSeparator();

    m_goto = m_groups->addMenu(tr("Go to:"));
    auto *a_goto = new QAction(QObject::tr("Create new group"), m_groups);
    QObject::connect(a_goto, &QAction::triggered, this, &WTGroups::create);
    m_groups->addAction(a_goto);

    a_del_group = new QAction("Delete current group", m_groups);
    QObject::connect(a_del_group, &QAction::triggered, [this]() { this->remove(); });
    m_groups->addAction(a_del_group);

    updateMenu();
}

void WTGroups::updateMenu() {
    a_del_group->setDisabled(current_group == NO_GROUP);

    m_add->clear();

    auto *a_add = new QAction(QObject::tr("Add to new group"), m_add);
    QObject::connect(a_add, &QAction::triggered, [this]() { this->create(true); });
    m_add->addAction(a_add);
    m_add->addSeparator();

    for (const QString &group : groups->names()) {
        if (group == NO_GROUP)
            continue;

        auto *t_action = new QAction(group, m_add);
        QObject::connect(t_action, &QAction::triggered, [this, group]() { this->addCurrentTabTo(group); });
        m_add->addAction(t_action);
    }

    m_goto->clear();
    for (const QString &group : groups->names()) {
        auto *a = new QAction(group, m_goto);
        QObject::connect(a, &QAction::triggered, [this, group]() { this->tabs->groupBy(group); });
        m_goto->addAction(a);
        a->setDisabled(group == current_group);
    }
}

QString WTGroups::setSelected(QString group) {
    if (group.isEmpty()) // If default
        group = GROUP_SELECTED_IF_NULL(groups->names());

    current_group = group;
    groups->setCurrent(group);

    l_group->setGroup(current_group);

    updateMenu();

    return group;
}

QString WTGroups::nextGroup() {
    return groups->nextGroup();
}
