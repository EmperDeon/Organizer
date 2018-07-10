/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_CAES_H
#define ORGANIZER_CAES_H

#include <vars.h>
#include "utils/Utils.h"
#include "Crypt.h"
#include "CBytes.h"


class CAes {
    unsigned int block_size;
    const CBytes key;

public:
    // Initialize AES
    // block_size should be multiple of 128
    CAes(unsigned int _block_size, const CBytes &_key);

    QString encrypt(const QString &message);

    CBytes encryptAr(CBytes message);

    QString decrypt(const QString &message);

    CBytes decryptAr(CBytes message);

protected:
    void handle_error(int err);

    CBytes generateIV();

    void addPadding(CBytes &message);

    void removePadding(CBytes &message);
};


#endif //ORGANIZER_CAES_H
