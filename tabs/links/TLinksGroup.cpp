/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <vendor/additions.h>
#include <utils/UScrollArea.h>
#include <utils/Utils.h>
#include <utils/logs/ULogger.h>
#include "TLinksGroup.h"

TLinksGroup::TLinksGroup(const json_o &o) : Tab(o, Tab::LinksGroup) {
    auto *scrollLayout = new QVBoxLayout;

    list = new QVBoxLayout;
    list->setAlignment(Qt::AlignTop);
    list->setContentsMargins(0, 0, 0, 0);

    auto *scroll = new UScrollArea(list);

    scrollLayout->addWidget(scroll);
    scrollLayout->setMargin(0);

    setLayout(scrollLayout);

    load();
}

void TLinksGroup::addLink(json_o o, int index) {
    if (o.isEmpty()) {
        o = R"({"name": "", "link": ""})"_json;
        index = list->count();
    }

    TLink *link = new TLink(this, o, index);

    links << link;
    list->addWidget(link);
}

void TLinksGroup::updateLinks() {
    if (!links.isEmpty() && !links.last()->isEmpty()) {
        addLink();
    }

    updated();
}

void TLinksGroup::swapLinks(int from_id, int to_id) {
    reloadJson([from_id, to_id](json &obj) {
        unsigned long size = obj.size() + 1;
        if (from_id > size || to_id > size) {
            logE("Trying to access undefined element: " + QString::number(from_id) + " || " + QString::number(to_id) +
                 ", where size is : " + QString::number(size - 1));
        } else {
            json val = obj[from_id];

            if (from_id < to_id) {
                obj.insert(obj.begin() + to_id, val);
                obj.erase(obj.begin() + from_id);
            } else {
                obj.erase(obj.begin() + from_id);
                obj.insert(obj.begin() + to_id, val);
            }
        }
    });
}

void TLinksGroup::fromJson(json v) {
    // Remove old links
    Utils::layoutClear(list);
    links.clear();

    // Add new links
    for (int i = 0; i < v.size(); i++) {
        addLink(v[i], i);
    }

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
