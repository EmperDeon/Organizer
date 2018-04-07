/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_SSETTINGS_H
#define ORGANIZER_SSETTINGS_H

#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include "Storage.h"

class Storage;

class SSettings {
    Storage *storage;

public:
    SSettings(Storage *stor = nullptr);

    QJsonObject object();

    QJsonValue get(const QString &key);

    bool getB(const QString &key);

    QString getS(const QString &key);

    int getI(const QString &key);

    void set(const QString &key, const QJsonValue &val);

    static QJsonArray allSettings();

    void initializeDefaults();
};


#endif //ORGANIZER_SSETTINGS_H
