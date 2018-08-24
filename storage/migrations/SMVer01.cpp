/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "SMVer01.h"

std::string SMVer01::getVersion() {
    return "0.1";
}

void SMVer01::processF(json_o &o) {}


void SMVer01::processD(json_o &o) {
    int type = o["type"];

    if (type == 4) {
        o["type"] = 2;
    }

    if (type == 8) {
        o["type"] = 4;
    }
}
