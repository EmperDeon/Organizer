/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <crypt/Crypt.h>
#include "SMVer02.h"

QString SMVer02::getVersion() {
    return "0.2";
}

QJsonObject SMVer02::processF(QJsonObject o) { return o; }


QJsonObject SMVer02::processD(QJsonObject o) {
    if (!o.contains("uuid")) {
        o["uuid"] = Crypt::generateUUID();
    }

    return o;
}
