/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <storage/Storage.h>
#include <widgets/WMain.h>
#include "WTSorter.h"

WTSorter::WTSorter() {
    auto *l = new QVBoxLayout();

    tree = new UTreeWidget;
    tree->setColumnCount(3);
    tree->setEditable(true);
    tree->setMovable(true);
    tree->setAutoResizable(true);
    l->addWidget(tree);


    auto *h_l = new QHBoxLayout;

    auto *b_c = new QPushButton(tr("Clear")),
            *b_q = new QPushButton(tr("Save and Reload tabs"));

    connect(b_c, &QPushButton::clicked, this, &WTSorter::reload);
    connect(b_q, &QPushButton::clicked, this, &WTSorter::accept);

    h_l->addWidget(b_c);
    h_l->addWidget(b_q);
    l->addLayout(h_l);

    setLayout(l);

    reload();
}

void WTSorter::reload() {
    tree->clear();
    tree->addRoot(tr("Tabs"));

    json_a groups = Storage::getInstance()->getDocs();

    for (const json_o &o_group : groups) {
        Tab::TabType type = Tab::tabType(o_group);

        auto *t_group = tree->addToRoot({o_group["name"], Tab::tabTypeS(type)});
        t_group->setData(2, Qt::UserRole, o_group.dumpQ());

        if (type == Tab::LinksGroup) {
            for (const auto &o_link : o_group["content"]) {

                auto *t_link = new QTreeWidgetItem(t_group, {o_link["name"], o_link["link"]});
                t_link->setData(2, Qt::UserRole, o_link.dumpQ());
            }
        }
    }
}

json_a WTSorter::toDocs() {
    auto *root = tree->topLevelItem(0);

    json_a docs;
    json_o new_groups;

    for (int i = 0; i < root->childCount(); i++) { // Collect groups from UTreeWidget
        auto *i_group = root->child(i);
        json_o o_group = json::parse(i_group->data(2, Qt::UserRole).toString().toStdString());
        Tab::TabType type = Tab::tabType(o_group);

        if (type == Tab::LinksGroup) {
            json_a links;

            for (int j = 0; j < i_group->childCount(); j++) { // Collect links from group
                auto *i_link = i_group->child(j);
                json_o o_link = json::parse(i_link->data(2, Qt::UserRole).toString().toStdString());

                o_link["name"] = i_link->data(0, Qt::DisplayRole).toString();
                o_link["link"] = i_link->data(1, Qt::DisplayRole).toString();

                links += o_link;
            }

            o_group["content"] = links;
        }

        o_group["name"] = i_group->data(0, Qt::DisplayRole).toString();

        docs += o_group;
    }

    return docs;
}

void WTSorter::sortTabs() {
    // To save any unsaved data
    WMain::getInstance()->contr->save();

    auto *w = new WTSorter;

    if (w->exec()) { // Reorder only if clicked "Save"
        json_a docs = w->toDocs();

        Storage::getInstance()->setDocs(docs);
        WMain::getInstance()->recreateTabs();
    }
}
