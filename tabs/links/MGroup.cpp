/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtCore/QJsonArray>
#include <utils/UScrollArea.h>
#include "MGroup.h"

MGroup::MGroup(const QJsonObject &o) : MTab(o, MTab::LinksGroup) {
    auto *scrollLayout = new QVBoxLayout;

    list = new QVBoxLayout;
    list->setAlignment(Qt::AlignTop);

    auto *scroll = new UScrollArea(list);

    scrollLayout->addWidget(scroll);
    scrollLayout->setMargin(0);

    setLayout(scrollLayout);

    load();
}

void MGroup::addLink(QJsonObject o) {
    MLink *link = new MLink(this, o);

    links << link;
    list->addWidget(link);
}

void MGroup::updateLinks() {
    if (!links.isEmpty() && !links.last()->isEmpty()) {
        addLink();
    }

    updated();
}

void MGroup::fromJson(QJsonValue v) {
    QJsonArray arr = v.toArray();

    for (QJsonValue t : arr)
        addLink(t.toObject());

    if (arr.empty())
        addLink();

    for (MLink *l : links)
        l->editChange();
}

QJsonValue MGroup::toJson() {
    QJsonArray r;
    for (MLink *l : links) {
        if (!l->isEmpty())
            r << l->getJson();
    }

    return r;
}
