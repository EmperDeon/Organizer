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

#include "include/Rsa.h"
#include <openssl/rsa.h>
#include <include/simple_ossl.h>

SimpleOSSL::RSAKey::RSAKey(EVP_PKEY *pkey, bool s) : evp(pkey), sec(s) {}

int SimpleOSSL::RSAKey::maximumEncryptSize() const {
    RSA *rsa = pkey()->pkey.rsa;

    return RSA_size(rsa) - 12;
}

QByteArray SimpleOSSL::RSAKey::encrypt(const QByteArray &in) {
    RSA *rsa = pkey()->pkey.rsa;
    QByteArray buf = in;
    int max = maximumEncryptSize();

    if (buf.size() > max)
        buf.resize(max);
    QByteArray result(RSA_size(rsa), 0);

    int pad = RSA_PKCS1_PADDING;
    int ret;

    if (isPrivate())
        ret = RSA_private_encrypt(buf.size(), (unsigned char *) buf.data(), (unsigned char *) result.data(),
                                  rsa,
                                  pad);
    else
        ret = RSA_public_encrypt(buf.size(), (unsigned char *) buf.data(), (unsigned char *) result.data(), rsa,
                                 pad);

    if (ret < 0)
        return QByteArray();
    result.resize(ret);

    return result;
}

QByteArray SimpleOSSL::RSAKey::decrypt(const QByteArray &in) {
    RSA *rsa = pkey()->pkey.rsa;
    QByteArray result(RSA_size(rsa), 0);
    int pad = RSA_PKCS1_PADDING;

    int ret;
    if (isPrivate())
        ret = RSA_private_decrypt(in.size(), (unsigned char *) in.data(), (unsigned char *) result.data(), rsa,
                                  pad);
    else
        ret = RSA_public_decrypt(in.size(), (unsigned char *) in.data(), (unsigned char *) result.data(), rsa,
                                 pad);

    if (ret < 0)
        return QByteArray();
    result.resize(ret);

    return result;
}

QByteArray SimpleOSSL::RSAKey::signMessage(const QByteArray &a) {
    evp.startSign();
    evp.update(a);
    return evp.endSign();
}

bool SimpleOSSL::RSAKey::verifyMessage(const QByteArray &a, const QByteArray &sig) {
    evp.startVerify();
    evp.update(a);
    return evp.endVerify(sig);
}

QString SimpleOSSL::RSAKey::toPEM(bool pub) {
    if (pub) {
        return publicToPEM(this);
    } else {
        return privateToPEM(this);
    }
}

SimpleOSSL::RSAKey *SimpleOSSL::RSAKey::generate(int size) {
    RSA *keypair = RSA_new();
    BIGNUM *bn = BN_new();
    BN_set_word(bn, RSA_F4);

    RSA_generate_key_ex(keypair, size, bn, nullptr);
    EVP_PKEY *evpkey = EVP_PKEY_new();
    EVP_PKEY_set1_RSA(evpkey, keypair);

    BN_free(bn);

    return new RSAKey(evpkey, true);
}

SimpleOSSL::EVPKey::EVPKey(EVP_PKEY *key) : pkey(key) {
    state = Idle;
}

SimpleOSSL::EVPKey::~EVPKey() {
    reset();
}

void SimpleOSSL::EVPKey::reset() {
    if (pkey)
        EVP_PKEY_free(pkey);
    pkey = nullptr;
    raw.clear();
}

void SimpleOSSL::EVPKey::startSign() {
    state = SignActive;
    EVP_MD_CTX_init(&mdctx);
    if (!EVP_SignInit_ex(&mdctx, EVP_sha256(), nullptr))
        state = SignError;

}

void SimpleOSSL::EVPKey::startVerify() {
    state = VerifyActive;
    EVP_MD_CTX_init(&mdctx);
    if (!EVP_VerifyInit_ex(&mdctx, EVP_sha256(), nullptr))
        state = VerifyError;
}

void SimpleOSSL::EVPKey::update(const QByteArray &in) {
    if (state == SignActive) {
        if (!EVP_SignUpdate(&mdctx, in.data(), (unsigned int) in.size()))
            state = SignError;
    } else if (state == VerifyActive) {
        if (!EVP_VerifyUpdate(&mdctx, in.data(), (unsigned int) in.size()))
            state = VerifyError;
    }
}

QByteArray SimpleOSSL::EVPKey::endSign() {
    if (state == SignActive) {
        QByteArray out(EVP_PKEY_size(pkey), 0);
        unsigned int len = out.size();

        if (!EVP_SignFinal(&mdctx, (unsigned char *) out.data(), &len, pkey)) {
            state = SignError;
            return QByteArray();
        }

        out.resize(len);
        state = Idle;
        return out;
    } else
        return QByteArray();
}

bool SimpleOSSL::EVPKey::endVerify(const QByteArray &sig) {
    if (state == VerifyActive) {
        if (EVP_VerifyFinal(&mdctx, (unsigned char *) sig.data(), (unsigned int) sig.size(), pkey) != 1) {
            state = VerifyError;
            return false;
        }
        state = Idle;
        return true;
    } else
        return false;
}
