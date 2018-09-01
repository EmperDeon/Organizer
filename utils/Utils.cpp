/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <vendor/additions.h>
#include <QtCore/QBuffer>
#include <QtCore/QDataStream>
#include "Utils.h"

QByteArray Utils::fromBase(const QString &str) {
    return QByteArray::fromBase64(str.toUtf8());
}

QString Utils::toBase(const QByteArray &arr) {
    return QString::fromUtf8(arr.toBase64());
}

QDate Utils::dateFromString(const QString &date) {
    return QDateTime::fromMSecsSinceEpoch(date.toULongLong() * 1000).date();
}

json_a Utils::arrayToJson(const QStringList &list) {
    json_a r;
    for (const QString &s : list) r += s;
    return r;
}

QStringList Utils::arrayFromJson(const json_a &value) {
    QStringList r;
    for (const auto &s : value) r << s.get<QString>();
    return r;
}

QString Utils::serializeToString(const QJsonValue &value) {
    QByteArray bytes;
    QDataStream out(&bytes, QIODevice::WriteOnly);

    out << value.toVariant();
    out.device()->close();

    return Utils::toBase(bytes);
}

QJsonValue Utils::serializeFromString(const QString &value) {
    QByteArray bytes = Utils::fromBase(value);
    QVariant variant;
    QDataStream in(&bytes, QIODevice::ReadOnly);

    in >> variant;

    return QJsonValue::fromVariant(variant);
}
