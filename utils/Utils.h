/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_CTOOLS_H
#define ORGANIZER_CTOOLS_H

#include <QtCore/QJsonValue>
#include <vendor/additions.h>
#include <QtCore/QDate>
#include <QtCore/QDateTime>
#include <QtCore/QVariant>
#include <QtWidgets/QBoxLayout>

#define select_if(from, to, predicate) std::copy_if((from).begin(), (from).end(), std::back_inserter(to), predicate)
#define collect(from, to, lambda) std::transform((from).begin(), (from).end(), std::back_inserter(to), lambda)
#define sort_by(collection, lambda) std::sort((collection).begin(), (collection).end(), (lambda))

class Utils {
public:
    static QByteArray fromBase(const QString &str);

    static QString toBase(const QByteArray &arr);

    static QDate dateFromString(const QString &date);

    static json_a arrayToJson(const QStringList &list);

    static QStringList arrayFromJson(const json &value);

    static QString serializeToString(const QJsonValue &value);

    static QJsonValue serializeFromString(const QString &value);

    static void layoutClear(QBoxLayout *layout);
};

#endif //ORGANIZER_CTOOLS_H
