/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <storage/migrations/SMVer0.h>
#include <storage/migrations/SMVer01.h>
#include <storage/migrations/SMVer02.h>
#include "SMigrations.h"

SMigrations::SMigrations() {
    migrations = {
            new SMVer0,
            new SMVer01,
            new SMVer02
    };
}

QJsonObject SMigrations::processFull(QJsonObject o) {
    for (auto m : migrations) {
        if (m->isNeeded(o)) {
            o = m->processF(o);
            o["version"] = m->getVersion();
        }
    }

    return o;
}

QJsonArray SMigrations::processDocs(QJsonArray a) {
    for (auto m : migrations) {
        QJsonArray r;

        for (auto v : a) {
            QJsonObject o = v.toObject();

            if (m->isNeeded(o)) {
                o = m->processD(o);
                o["version"] = m->getVersion();
            }
            r << o;
        }
        a = r;
    }

    return a;
}

QJsonObject SMigrations::processFiles(QJsonObject a) {
    // FIXME: Stub, add realization later

    return a;
}
