/*
	Copyright (c) 2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_CRYPT_H
#define ORGANIZER_CRYPT_H

#include <tomcrypt.h>
#include <utils/USingleton.h>
#include "CBytes.h"


class Crypt : public USingleton<Crypt> {
    prng_state *random_state = nullptr;

public:
    // Check algorithms and initialize random
    Crypt();

    static CBytes randomBytes(int size);

    static CBytes salt();

    static QString hash(CBytes input);

    static QString hashFile(const QString &filename);

    static CBytes deriveKey(const QString &str, int index = 0, int length = 32);
};


#endif //ORGANIZER_CRYPT_H
