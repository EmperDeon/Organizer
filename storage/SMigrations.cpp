/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <storage/migrations/SMVer1.h>
#include "SMigrations.h"

SMigrations::SMigrations() {
    migrations = {
            new SMVer1
    };
}

QJsonObject SMigrations::processFull(QJsonObject o) {
    for (auto m : migrations) {
        if (m->isNeededF(o))
            o = m->processF(o);
    }

    return o;
}

QJsonArray SMigrations::processDocs(QJsonArray a) {
    for (auto m : migrations) {
        QJsonArray r;

        for (auto v : a) {
            QJsonObject o = v.toObject();

            if (m->isNeededD(o))
                o = m->processD(o);

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
