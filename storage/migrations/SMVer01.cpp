/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "SMVer01.h"

QString SMVer01::getVersion() {
    return "0.1";
}

QJsonObject SMVer01::processF(QJsonObject o) { return o; }


QJsonObject SMVer01::processD(QJsonObject o) {
    int type = o["type"].toInt();

    if (type == 4) {
        o["type"] = 2;
    }

    if (type == 8) {
        o["type"] = 4;
    }

    return o;
}
