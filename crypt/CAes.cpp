/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "CAes.h"
#include <vendor/simple_ossl/include/simple_ossl.h>

using namespace SimpleOSSL;

CAes::CAes(const char *cipher_name, QString k) : key(Utils::fromBase(k)), cipher(cipher_name) {}

QString CAes::encrypt(const QString &message) {
    return Utils::toBase(encryptAr(message.toLatin1()));
}

QByteArray CAes::encryptAr(const QByteArray &message) {
    return aesEncrypt(cipher, key, message);
}

QString CAes::decrypt(const QString &message) {
    return QString::fromLatin1(decryptAr(Utils::fromBase(message)));
}

QByteArray CAes::decryptAr(const QByteArray &message) {
    return aesDecrypt(cipher, key, message);
}
