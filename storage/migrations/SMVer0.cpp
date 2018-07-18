/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "SMVer0.h"
#include <utils/Utils.h>

QString SMVer0::getVersion() {
    return "0.0";
}

QJsonObject SMVer0::processF(QJsonObject o) {
    QString d = o["docs"].toString();

    // Collect all docs to one array
    QJsonArray r;
    QJsonObject doc, obj = Utils::fromJson(d);

    doc = obj["documents"].toObject();
    for (const QString &v : doc.keys()) {
        r << doc[v];
    }

    doc = obj["links"].toObject();
    for (const QString &v : doc.keys()) {
        QJsonObject t = doc[v].toObject();

        t["type"] = 2;

        r << t;
    }

    o["docs"] = Utils::toJson(r);

    return o;
}

QJsonObject SMVer0::processD(QJsonObject o) {
    switch (o["type"].toInt()) {
        case 0:
            o["content"] = o["text"].toString();
            o["type"] = 1;
            o.remove("text");
            break;

        case 1:
            o["content"] = o["lines"].toArray();
            o["type"] = 2;
            o.remove("lines");
            break;

        case 2:
            o["content"] = o["links"].toArray();
            o["type"] = 4;
            o.remove("links");
            break;

        default:;
    }

    return o;
}
