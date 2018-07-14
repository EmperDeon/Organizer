/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtCore/QJsonArray>
#include <utils/UScrollArea.h>
#include "TLinksGroup.h"

TLinksGroup::TLinksGroup(const QJsonObject &o) : Tab(o, Tab::LinksGroup) {
    auto *scrollLayout = new QVBoxLayout;

    list = new QVBoxLayout;
    list->setAlignment(Qt::AlignTop);

    auto *scroll = new UScrollArea(list);

    scrollLayout->addWidget(scroll);
    scrollLayout->setMargin(0);

    setLayout(scrollLayout);

    load();
}

void TLinksGroup::addLink(QJsonObject o) {
    TLink *link = new TLink(this, o);

    links << link;
    list->addWidget(link);
}

void TLinksGroup::updateLinks() {
    if (!links.isEmpty() && !links.last()->isEmpty()) {
        addLink();
    }

    updated();
}

void TLinksGroup::fromJson(QJsonValue v) {
    QJsonArray arr = v.toArray();

    for (QJsonValue t : arr)
        addLink(t.toObject());

    if (arr.empty())
        addLink();

    for (TLink *l : links)
        l->editChange();
}

QJsonValue TLinksGroup::toJson() {
    QJsonArray r;
    for (TLink *l : links) {
        if (!l->isEmpty())
            r << l->getJson();
    }

    return r;
}
