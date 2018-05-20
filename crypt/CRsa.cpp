/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "CRsa.h"
#include "utils/Utils.h"

// TODO: Add key checks to encode, ..., verify

CRsa::CRsa(RSAKey *priv_key) : private_key(priv_key) {}

CRsa::CRsa(QString pub, QString prv, QString passphrase) {
    if (!pub.isEmpty())
        public_key = publicFromPEM(pub);

    if (!prv.isEmpty())
        private_key = privateFromPEM(prv, passphrase.toLatin1());
}

QString CRsa::encode(QString str) {
    return Utils::toBase(public_key->encrypt(str.toLatin1()));
}

QString CRsa::decode(QString str) {
    return QString::fromLatin1(private_key->decrypt(Utils::fromBase(str)));
}

QString CRsa::sign(QString str) {
    return Utils::toBase(private_key->signMessage(str.toLatin1()));
}

bool CRsa::verify(QString str, QString sig) {
    return public_key->verifyMessage(str.toLatin1(), Utils::fromBase(sig));
}

QString CRsa::getPrivateKey() {
    if (private_key != nullptr) {
        return private_key->toPEM();
    } else
        return "";
}

QString CRsa::getPublicKey() {
    if (public_key != nullptr) {
        return public_key->toPEM(true);
    } else if (private_key != nullptr) {
        return private_key->toPEM();
    } else
        return "";
}

CRsa::~CRsa() {
    if (public_key != nullptr)
        delete public_key;

    if (private_key != nullptr)
        delete private_key;
}

CRsa CRsa::createNew(int size) {
    return CRsa(RSAKey::generate(size));
}
