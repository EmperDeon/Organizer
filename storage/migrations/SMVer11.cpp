/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "SMVer11.h"

QString SMVer11::getVersion() {
    return "1.1";
}

QJsonObject SMVer11::processF(QJsonObject o) { return o; }


QJsonObject SMVer11::processD(QJsonObject o) {
    int type = o["type"].toInt();

    if (type == 4) {
        o["type"] = 2;
    }

    if (type == 8) {
        o["type"] = 4;
    }

    return o;
}
