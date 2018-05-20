/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_CRSA_H
#define ORGANIZER_CRSA_H

#include <vars.h>
#include <vendor/simple_ossl/include/simple_ossl.h>

using namespace SimpleOSSL;


class CRsa {
    RSAKey *private_key = nullptr, *public_key = nullptr;

public:
    explicit CRsa(RSAKey *priv_key);

    explicit CRsa(QString pub, QString prv = "", QString passphrase = "");

    QString encode(QString str);

    QString decode(QString str);

    QString sign(QString str);

    bool verify(QString str, QString sig);

    QString getPrivateKey();

    QString getPublicKey();

    ~CRsa();

    static CRsa createNew(int size = RSA_DEFAULT_SIZE);
};


#endif //ORGANIZER_CRSA_H
