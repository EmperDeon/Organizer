/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_CTOOLS_H
#define ORGANIZER_CTOOLS_H

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
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

    static QString toJson(QJsonArray ob, QJsonDocument::JsonFormat format = QJsonDocument::Compact);

    static QString toJson(QJsonObject ob, QJsonDocument::JsonFormat format = QJsonDocument::Compact);

    static QJsonObject fromJson(const QString &str);

    static QJsonArray fromJsonA(const QString &str);

    static QDate dateFromString(const QString &date);

    static QJsonArray arrayToJson(const QStringList &list);

    static QStringList arrayFromJson(const QJsonValue &value);

    static QString serializeToString(const QJsonValue &value);

    static QJsonValue serializeFromString(const QString &value);

    static void removeInArray(QJsonArray &array, const QJsonValue &val);

    static void layoutClear(QBoxLayout *layout);
};

#endif //ORGANIZER_CTOOLS_H
