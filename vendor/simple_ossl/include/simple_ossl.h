/*
 * Copyright (C) 2003-2007  Justin Karneges <justin@affinix.com>
 * Copyright (C) 2004,2005  Brad Hards <bradh@frogmouth.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301  USA
 *
 */

#ifndef SIMPLE_OSSL_H
#define SIMPLE_OSSL_H

#include <QtCore/QByteArray>
#include "Rsa.h"


namespace SimpleOSSL {
    /*
     * Initialize OpenSSL
     * */
    void init();

    /*
     * Encrypts ByteArray with Aes cipher
     *
     * IV is generated and embedded as first 16 bytes
     * */
    QByteArray aes_encrypt(const QString &cipher, const QByteArray &key, const QByteArray &data);


    /*
     * Decrypts ByteArray with Aes cipher
     *
     * IV is first 16 bytes of ByteArray
     * */
    QByteArray aes_decrypt(const QString &cipher, const QByteArray &key, QByteArray data);


    /*
     * Convert RSAKey to Public PEM
     * */
    QString publicToPEM(RSAKey *k);

    /*
     * Create RSAKey from Public PEM
     * */
    RSAKey *publicFromPEM(const QString &s);

    /*
     * Convert RSAKey to Private PEM
     * */
    QString privateToPEM(RSAKey *k, const QByteArray &passphrase = QByteArray());

    /*
     * Create RSAKey from Private PEM
     * */
    RSAKey *privateFromPEM(const QString &s, const QByteArray &passphrase = QByteArray());


    /*
     * Creates SHA256 hash from ByteArray
     * */
    QString sha256(const QByteArray &a);
};

// EVP_sha256();

#endif // SIMPLE_OSSL_H
