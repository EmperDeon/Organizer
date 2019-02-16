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

void SMigrations::processFull(json_o &o) {
    if (o.isEmpty()) {
        return;
    }

    for (auto m : migrations) {
        if (m->isNeeded(o)) {
            m->processF(o);
            o["version"] = m->getVersion();
        }
    }
}

void SMigrations::processDocs(json_o &docs) {
    for (auto m : migrations) {
        for (const auto &it : docs.items()) {
            if (m->isNeeded(it.value())) {
                json obj = it.value();
                m->processD(obj);
                obj["version"] = m->getVersion();

                docs[it.key()] = obj;
            }
        }
    }
}

void SMigrations::processFiles(json_o &) {
    // FIXME: Stub, add realization later

}
