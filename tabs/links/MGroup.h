/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_MGROUP_H
#define ORGANIZER_MGROUP_H

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QScrollArea>
#include <tabs/links/MLink.h>
#include <tabs/MTab.h>

class MLink;


class MGroup : public MTab {
    QList<MLink *> links;

    QVBoxLayout *list;


public:
    explicit MGroup(const QJsonObject &o);

    void addLink(QJsonObject o = QJsonObject());

    void updateLinks();

    void fromJson(QJsonValue v) override;

    QJsonValue toJson() override;
};


#endif //ORGANIZER_MGROUP_H
