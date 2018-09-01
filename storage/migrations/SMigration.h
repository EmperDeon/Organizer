/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_SMIGRATION_H
#define ORGANIZER_SMIGRATION_H

#include <vendor/additions.h>
#include <vendor/additions.h>


class SMigration {
public:
    SMigration() = default;

    virtual std::string getVersion() = 0;

    virtual bool isNeeded(const json_o &o) {
        std::string ver = o["version"];
        return ver < getVersion();
    }

    // Full object
    virtual void processF(json_o &o) = 0;

    // Documents
    virtual void processD(json_o &o) = 0;
};


#endif //ORGANIZER_SMIGRATION_H
