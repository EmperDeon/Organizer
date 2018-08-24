/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_SMAP_H
#define ORGANIZER_SMAP_H

#include <QtCore/QString>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <utils/UOrderedMap.h>
#include <vendor/additions.h>

/*
 * Sorting by "sort_by" index in QJsonObject
 * */
class SMap : public UOrderedMap<QString, json> {

public:
    SMap() = default;

    void fromJson(const json &obj);

    json_o toJson();

    QString nextKey(const QString &key);
};


#endif //ORGANIZER_SMAP_H
