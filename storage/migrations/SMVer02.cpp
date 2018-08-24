/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <crypt/Crypt.h>
#include "SMVer02.h"

std::string SMVer02::getVersion() {
    return "0.2";
}

void SMVer02::processF(json_o &o) {}


void SMVer02::processD(json_o &o) {
    if (!o.contains("uuid")) {
        o["uuid"] = Crypt::generateUUID();
    }
}
