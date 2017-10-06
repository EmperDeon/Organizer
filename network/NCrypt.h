/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_NCRYPT_H
#define ORGANIZER_NCRYPT_H

#include <crypt/CAes.h>
#include <storage/Storage.h>

class NCrypt {
    Storage *st;

public:
    NCrypt() : st(Storage::getInstance()) {}

    QByteArray encrypt(QByteArray mem, QString path);

    QByteArray decrypt(QByteArray mes, QString path);

    QString getKey(QString path);

    QString sign(QString mes);

    bool verify(QString mes, QString sign);
};


#endif //ORGANIZER_NCRYPT_H
