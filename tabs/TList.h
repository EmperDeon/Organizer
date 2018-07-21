/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_TLIST_H
#define ORGANIZER_TLIST_H

#include <utils/UOrderedMap.h>
#include "Tab.h"


class TList : public UOrderedMap<QString, Tab *> {

public:
    TList() = default;

    void fromJson(const QJsonObject &obj);

    void fromJson(const QJsonArray &arr);

    Tab *addJson(const QString &key, const QJsonObject &obj);

    QJsonObject toJson();

    QJsonArray toJsonA();

    static Tab *createNew(const QJsonObject &o, int i_type = -1);
};


#endif //ORGANIZER_TLIST_H
