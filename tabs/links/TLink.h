/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_TLINK_H
#define ORGANIZER_TLINK_H

#include <QtCore/QJsonObject>
#include <QtWidgets/QLineEdit>
#include <tabs/links/TLinksGroup.h>

class TLinksGroup;


class TLink : public QWidget {
    TLinksGroup *group;

    QLineEdit *l_name, *l_link;

    bool empty = true;

public:
    explicit TLink(TLinksGroup *g, QJsonObject o = QJsonObject());

    bool isEmpty() const { return empty; }

    QJsonObject getJson() const;

    void editChange();

public:
    bool eventFilter(QObject *object, QEvent *event) override;
};


#endif //ORGANIZER_TLINK_H
