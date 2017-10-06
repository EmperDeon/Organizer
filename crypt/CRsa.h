/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_RSA_H
#define ORGANIZER_RSA_H

#include <Qca-qt5/QtCrypto/QtCrypto>
#include <vars.h>

class CRsa {
    QCA::PrivateKey privateKey;
    QCA::PublicKey publicKey;

public:
    explicit CRsa(QString pub, QString prv = "", QString passphrase = "");

    static QString createPrivateKey(int size = RSA_DEFAULT_SIZE);

    static QString createPublicKey(QString private_key);

    QString encode(QString str);

    QString decode(QString str);

    QString sign(QString str);

    bool verify(QString str, QString sig);

    QString getPrivateKey();

    QString getPublicKey();
};


#endif //ORGANIZER_RSA_H
