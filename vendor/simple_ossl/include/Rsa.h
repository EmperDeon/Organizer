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

#ifndef SIMPLE_OSSL_RSA_H
#define SIMPLE_OSSL_RSA_H

#include <QtCore/QByteArray>
#include <QtCore/QString>
#include <openssl/evp.h>
#include "Utils.h"


namespace SimpleOSSL {
    class EVPKey {
    public:
        enum State {
            Idle, SignActive, SignError, VerifyActive, VerifyError
        };

        EVP_PKEY *pkey;
        EVP_MD_CTX mdctx;
        State state;
        QByteArray raw;

        explicit EVPKey(EVP_PKEY *key);

        ~EVPKey();

        void reset();

        void startSign();

        void startVerify();

        void update(const QByteArray &in);

        QByteArray endSign();

        bool endVerify(const QByteArray &sig);
    };


    class RSAKey {
        EVPKey evp;
        bool sec;

    public:
        RSAKey(EVP_PKEY *pkey, bool s);

        bool isPrivate() const { return sec; }

        EVP_PKEY *pkey() const { return evp.pkey; }

        QString toPEM(bool pub = false);

        int maximumEncryptSize() const;

        QByteArray encrypt(const QByteArray &in);

        QByteArray decrypt(const QByteArray &in);

        QByteArray signMessage(const QByteArray &a);

        bool verifyMessage(const QByteArray &a, const QByteArray &sig);

        static RSAKey *generate(int size = 2048);
    };
}

#endif //SIMPLE_OSSL_RSA_H
