/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_SMIGRATIONS_H
#define ORGANIZER_SMIGRATIONS_H

#include <QtCore/QList>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <storage/migrations/SMigration.h>
#include <vendor/additions.h>


class SMigrations {
    QList<SMigration *> migrations;


public:
    explicit SMigrations();

    void processFull(json_o &o);

    void processDocs(json_a &a);

    void processFiles(json_o &a);
};


#endif //ORGANIZER_SMIGRATIONS_H
