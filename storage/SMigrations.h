/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_SMIGRATIONS_H
#define ORGANIZER_SMIGRATIONS_H

#include <QtCore/QList>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <storage/migrations/SMigration.h>


class SMigrations {
    QList<SMigration *> migrations;


public:
    explicit SMigrations();

    QJsonObject processFull(QJsonObject o);

    QJsonArray processDocs(QJsonArray a);

    QJsonObject processFiles(QJsonObject a);
};


#endif //ORGANIZER_SMIGRATIONS_H
