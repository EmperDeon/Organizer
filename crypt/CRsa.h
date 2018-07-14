/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_CRSA_H
#define ORGANIZER_CRSA_H

#include <vars.h>
#include <tomcrypt.h>


class CRsa {
    rsa_key *key;

public:
    explicit CRsa(rsa_key *_key);

    explicit CRsa(const QString &_key, bool _private = false);

    QString encode(QString str);

    QString decode(QString str);

    QString sign(QString str);

    bool verify(QString str, QString sig);

    QString privateKey();

    QString publicKey();

    ~CRsa();

    static CRsa generatePrivate(int size = RSA_DEFAULT_SIZE);
};


#endif //ORGANIZER_CRSA_H
