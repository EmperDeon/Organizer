/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_SSETTINGS_H
#define ORGANIZER_SSETTINGS_H

#include <QtCore/QJsonObject>


class SSettings {
public:
    static QJsonObject object();

    static QJsonValue get(const QString &key);

    static bool getB(const QString &key);

    static QString getS(const QString &key);

    static void set(const QString &key, const QJsonValue &val);

    static QJsonArray allSettings();

    static void initializeDefaults();
};


#endif //ORGANIZER_SSETTINGS_H
