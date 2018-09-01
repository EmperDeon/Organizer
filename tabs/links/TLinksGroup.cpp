/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <vendor/additions.h>
#include <utils/UScrollArea.h>
#include <utils/Utils.h>
#include "TLinksGroup.h"

TLinksGroup::TLinksGroup(const json_o &o) : Tab(o, Tab::LinksGroup) {
    auto *scrollLayout = new QVBoxLayout;

    list = new QVBoxLayout;
    list->setAlignment(Qt::AlignTop);

    auto *scroll = new UScrollArea(list);

    scrollLayout->addWidget(scroll);
    scrollLayout->setMargin(0);

    setLayout(scrollLayout);

    load();
}

void TLinksGroup::addLink(json_o o) {
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

void TLinksGroup::fromJson(json v) {
    // Remove old links
    Utils::layoutClear(list);
    links.clear();

    // Add new links
    for (json t : v)
        addLink(t);

    if (v.empty())
        addLink();

    for (TLink *l : links)
        l->editChange();
}

json TLinksGroup::toJson() {
    json_a r;

    for (TLink *l : links) {
        if (!l->isEmpty())
            r += l->getJson();
    }

    return r;
}
