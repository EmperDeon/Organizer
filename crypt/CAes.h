/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_CAES_H
#define ORGANIZER_CAES_H

#include <vars.h>
#include "utils/Utils.h"


class CAes {
    QByteArray key;
    const char *cipher;

public:
    CAes(const char *cipher_name, QString k);

    QString encrypt(const QString &message);

    QByteArray encryptAr(const QByteArray &message);

    QString decrypt(const QString &message);

    QByteArray decryptAr(const QByteArray &message);
};


#endif //ORGANIZER_CAES_H
