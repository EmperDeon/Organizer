/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_TLINK_H
#define ORGANIZER_TLINK_H

#include <vendor/additions.h>
#include <QtWidgets/QLineEdit>
#include <tabs/links/TLinksGroup.h>
#include <utils/widgets/draggable/UDraggableItem.h>

class TLinksGroup;


class TLink : public UDraggableItem {
    TLinksGroup *group;

    QLineEdit *l_name, *l_link;

    bool empty = true;

public:
    explicit TLink(TLinksGroup *g, json_o o, int id);

    bool isEmpty() const { return empty; }

    json_o getJson() const;

    void editChange();

    void itemDropped(int dropped_id, int at_id) override;

    bool itemEventFilter(QObject *object, QEvent *event) override;
};


#endif //ORGANIZER_TLINK_H
