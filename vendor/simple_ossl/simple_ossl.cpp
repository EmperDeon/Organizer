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

#include "include/simple_ossl.h"
#include <include/Aes.h>
#include <include/Hash.h>
#include <QDebug>

void SimpleOSSL::init() {
    OpenSSL_add_all_algorithms();
}

QByteArray SimpleOSSL::aesEncrypt(const char *cipher, const QByteArray &key, const QByteArray &data) {
    Aes *aes;
    QByteArray iv = Aes::generateIV(), out, fout;

    if (strcmp(cipher, "128") == 0) {
        aes = new Aes(EVP_aes_128_cbc());
    } else if (strcmp(cipher, "256") == 0) {
        aes = new Aes(EVP_aes_256_cbc());
    } else {
        return QByteArray();
    }

    aes->setup(Encode, key, iv);

    bool ok = aes->update(data, &out) && aes->final(&fout);
    delete aes;

    if (!ok)
        return QByteArray();
    else
        return iv + out + fout;
}

QByteArray SimpleOSSL::aesDecrypt(const char *cipher, const QByteArray &key, QByteArray data) {
    Aes *aes;

    QByteArray iv = data.mid(0, SIMPLE_OSSL_IV_SIZE), out, fout;
    data.remove(0, SIMPLE_OSSL_IV_SIZE);

    if (strcmp(cipher, "128") == 0) {
        aes = new Aes(EVP_aes_128_cbc());
    } else if (strcmp(cipher, "256") == 0) {
        aes = new Aes(EVP_aes_256_cbc());
    } else {
        return QByteArray();
    }

    aes->setup(Decode, key, iv);

    bool ok = aes->update(data, &out) && aes->final(&fout);
    delete aes;

    if (!ok)
        return QByteArray();
    else
        return out + fout;
}

QString SimpleOSSL::generateAesKeyStr(int size) {
    return toBase64(Aes::generateKey(size));
}

QString SimpleOSSL::publicToPEM(SimpleOSSL::RSAKey *k) {
    EVP_PKEY *pkey = k->pkey();

    BIO *bo = BIO_new(BIO_s_mem());
    PEM_write_bio_PUBKEY(bo, pkey);
    QByteArray buf = bio2buf(bo);
    return QString::fromLatin1(buf);
}

SimpleOSSL::RSAKey *SimpleOSSL::publicFromPEM(const QString &s) {
    QByteArray in = s.toLatin1();
    BIO *bi = BIO_new(BIO_s_mem());
    BIO_write(bi, in.data(), in.size());
    EVP_PKEY *pkey = PEM_read_bio_PUBKEY(bi, nullptr, nullptr, nullptr);
    BIO_free(bi);

    if (pkey)
        return new RSAKey(pkey, false);
    else
        return nullptr;
}

QString SimpleOSSL::privateToPEM(SimpleOSSL::RSAKey *k, const QByteArray &passphrase) {
    if (!k->isPrivate())
        return "";

    const EVP_CIPHER *cipher = EVP_aes_256_cbc();
    EVP_PKEY *pkey = k->pkey();

    BIO *bo = BIO_new(BIO_s_mem());
    if (!passphrase.isEmpty())
        PEM_write_bio_PKCS8PrivateKey(bo, pkey, cipher, const_cast<char *>(passphrase.data()), passphrase.size(),
                                      nullptr, nullptr);
    else
        PEM_write_bio_PKCS8PrivateKey(bo, pkey, nullptr, nullptr, 0, nullptr, nullptr);

    QByteArray buf = bio2buf(bo);
    return QString::fromLatin1(buf);
}

SimpleOSSL::RSAKey *SimpleOSSL::privateFromPEM(const QString &s, const QByteArray &passphrase) {
    QByteArray in = s.toLatin1();
    BIO *bi = BIO_new(BIO_s_mem());
    BIO_write(bi, in.data(), in.size());
    EVP_PKEY *pkey;
    if (!passphrase.isEmpty())
        pkey = PEM_read_bio_PrivateKey(bi, nullptr, nullptr, (void *) passphrase.data());
    else
        pkey = PEM_read_bio_PrivateKey(bi, nullptr, nullptr, nullptr);
    BIO_free(bi);

    if (pkey)
        return new RSAKey(pkey, true);
    else
        return nullptr;
}

QString SimpleOSSL::sha256(const QByteArray &a) {
    Hash hash(EVP_sha256());
    return hash.hashToString(a);
}
