/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtCore/QJsonObject>
#include <QtCore/QBuffer>
#include <QtCore/QDataStream>
#include "Utils.h"

QByteArray Utils::fromBase(const QString &str) {
    return QByteArray::fromBase64(str.toUtf8());
}

QString Utils::toBase(const QByteArray &arr) {
    return QString::fromUtf8(arr.toBase64());
}

QString Utils::toJson(QJsonArray ob, QJsonDocument::JsonFormat format) {
    return QString::fromUtf8(QJsonDocument(ob).toJson(format));
}

QString Utils::toJson(QJsonObject ob, QJsonDocument::JsonFormat format) {
    return QString::fromUtf8(QJsonDocument(ob).toJson(format));
}

QJsonObject Utils::fromJson(const QString &str) {
    return QJsonDocument::fromJson(str.toUtf8()).object();
}

QJsonArray Utils::fromJsonA(const QString &str) {
    return QJsonDocument::fromJson(str.toUtf8()).array();
}

QDate Utils::dateFromString(const QString &date) {
    return QDateTime::fromMSecsSinceEpoch(date.toULongLong() * 1000).date();
}

QJsonArray Utils::arrayToJson(const QStringList &list) {
    QJsonArray r;
    for (const QString &s : list) r << s;
    return r;
}

QStringList Utils::arrayFromJson(const QJsonValue &value) {
    QStringList r;
    for (const auto &s : value.toArray()) r << s.toString();
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

void Utils::removeInArray(QJsonArray &array, const QJsonValue &val) {
    for (int i = 0; i < array.size(); i++) {
        if (array.at(i) == val) {
            array.removeAt(i);
            i--;
        }
    }
}
