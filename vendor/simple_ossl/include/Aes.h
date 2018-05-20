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

#ifndef SIMPLE_OSSL_AES_H
#define SIMPLE_OSSL_AES_H

#include <openssl/rand.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/x509v3.h>
#include <openssl/pkcs12.h>
#include <openssl/ssl.h>
#include <QtCore/QByteArray>

#define SIMPLE_OSSL_IV_SIZE 16


namespace SimpleOSSL {
    /**
       Direction settings for symmetric algorithms

       For some algorithms, it makes sense to have a "direction", such
       as Cipher algorithms which can be used to encrypt or decrypt.
    */
    enum Direction {
        Encode, ///< Operate in the "forward" direction; for example, encrypting
        Decode  ///< Operate in the "reverse" direction; for example, decrypting
    };

    class Aes {
        EVP_CIPHER_CTX m_context;
        const EVP_CIPHER *m_cryptoAlgorithm;

        Direction m_direction;
        bool m_ok;

    public:
        explicit Aes(const EVP_CIPHER *algorithm);

        void setup(Direction dir, const QByteArray &key, const QByteArray &iv);

        bool update(const QByteArray &in, QByteArray *out);

        bool final(QByteArray *out);

        QByteArray process(QByteArray &a);

        int blockSize() const;

        bool ok() { return m_ok; };

        ~Aes();

        static QByteArray generateIV();

        static QByteArray generateKey(int size = 32);
    };
}

#endif //SIMPLE_OSSL_AES_H
