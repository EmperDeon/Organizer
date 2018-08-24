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
    for (auto m : migrations) {
        if (m->isNeeded(o)) {
            m->processF(o);
            o["version"] = m->getVersion();
        }
    }
}

void SMigrations::processDocs(json_a &a) {
    for (auto m : migrations) {
        json_a result;

        for (const auto &o : a) {
            if (m->isNeeded(o)) {
                json obj = o;
                m->processD(obj);
                obj["version"] = m->getVersion();

                result += obj;
            }
        }

        a = std::move(result);
    }
}

void SMigrations::processFiles(json_o &a) {
    // FIXME: Stub, add realization later

}
