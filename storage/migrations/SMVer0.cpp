/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "SMVer0.h"
#include <utils/Utils.h>

std::string SMVer0::getVersion() {
    return "0.0";
}

void SMVer0::processF(json_o &o) {
    QString d = o["docs"];

    // Collect all docs to one array
    json_a r;
    json_o doc, obj = json::parse(d.toStdString());

    doc = obj["documents"];
    for (const auto &v : doc.keys()) {
        r += doc[v];
    }

    doc = obj["links"];
    for (const auto &v : doc.keys()) {
        json_o t = doc[v];

        t["type"] = 2;

        r += t;
    }

    o["docs"] = r.dumpQ();
}

void SMVer0::processD(json_o &o) {
    int type = o["type"];
    switch (type) {
        case 0:
            o["content"] = o["text"];
            o["type"] = 1;
            o.erase("text");
            break;

        case 1:
            o["content"] = o["lines"];
            o["type"] = 2;
            o.erase("lines");
            break;

        case 2:
            o["content"] = o["links"];
            o["type"] = 4;
            o.erase("links");
            break;

        default:;
    }
}
