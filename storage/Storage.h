/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_MIO_H
#define ORGANIZER_MIO_H

#include <vars.h>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <storage/SSecure.h>
#include <storage/SSettings.h>
#include <storage/SMigrations.h>
#include <utils/USingleton.h>
#include <vendor/additions.h>
#include "plugins/tabs/PTabFiles.h"
#include "SMap.h"

class PTabFiles;

class SSettings;

class Storage : public USingleton<Storage> {
    json_o original;
    json_a docs;

    SSecure *secure;
    SMigrations *migrations;

    bool loaded = false;

public:
    Storage();

    // redirect to original Json
    json &get(const QString &k) { return original[k]; }

    QString getS(const QString &k) { return get(k); }

    bool getB(const QString &k) { return get(k); }

    SMap getMap(const QString &k);

    Storage *set(const QString &k, const json &v) {
        original[k] = v;
        return this;
    }

    void remove(const QString &k) { original.erase(k); }

    json_a &getDocs() { return docs; }

    void setDocs(const json_a &doc) { docs = doc; }

    // IO
    void loadJson();

    void saveJson();

    void sendDocsToServer();

    // Docs, TODO: Review, maybe move to separate file
    void loadDocs(QString d);

    QString saveDocs();


    static SSecure *secureStorage() {
        Storage *st = getInstance();

        return st->secure;
    }

    void checkDir();
};

#endif //ORGANIZER_MIO_H
