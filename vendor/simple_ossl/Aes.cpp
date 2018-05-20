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

#include "include/Aes.h"
#include "include/Utils.h"

SimpleOSSL::Aes::Aes(const EVP_CIPHER *algorithm) {
    m_cryptoAlgorithm = algorithm;
    EVP_CIPHER_CTX_init(&m_context);
}

void SimpleOSSL::Aes::setup(Direction dir, const QByteArray &key, const QByteArray &iv) {
    m_direction = dir;

    if (Encode == m_direction) {
        EVP_EncryptInit_ex(&m_context, m_cryptoAlgorithm, nullptr, nullptr, nullptr);
        EVP_CIPHER_CTX_set_key_length(&m_context, key.size());
        EVP_EncryptInit_ex(&m_context, nullptr, nullptr,
                           (const unsigned char *) (key.data()),
                           (const unsigned char *) (iv.data()));
    } else {
        EVP_DecryptInit_ex(&m_context, m_cryptoAlgorithm, nullptr, nullptr, nullptr);
        EVP_CIPHER_CTX_set_key_length(&m_context, key.size());
        EVP_DecryptInit_ex(&m_context, nullptr, nullptr,
                           (const unsigned char *) (key.data()),
                           (const unsigned char *) (iv.data()));
    }

    EVP_CIPHER_CTX_set_padding(&m_context, 1);
}

bool SimpleOSSL::Aes::update(const QByteArray &in, QByteArray *out) {
    // This works around a problem in OpenSSL, where it asserts if
    // there is nothing to encrypt.
    if (0 == in.size())
        return true;

    out->resize(in.size() + blockSize());
    int resultLength;
    if (Encode == m_direction) {
        if (0 == EVP_EncryptUpdate(&m_context,
                                   (unsigned char *) out->data(),
                                   &resultLength,
                                   (unsigned char *) in.data(),
                                   in.size())) {
            return false;
        }
    } else {
        if (0 == EVP_DecryptUpdate(&m_context,
                                   (unsigned char *) out->data(),
                                   &resultLength,
                                   (unsigned char *) in.data(),
                                   in.size())) {
            return false;
        }
    }
    out->resize(resultLength);
    return true;
}

bool SimpleOSSL::Aes::final(QByteArray *out) {
    out->resize(blockSize());
    int resultLength;
    if (Encode == m_direction) {
        if (0 == EVP_EncryptFinal_ex(&m_context,
                                     (unsigned char *) out->data(),
                                     &resultLength)) {
            return false;
        }
    } else {
        if (0 == EVP_DecryptFinal_ex(&m_context,
                                     (unsigned char *) out->data(),
                                     &resultLength)) {
            return false;
        }
    }
    out->resize(resultLength);
    return true;
}

QByteArray SimpleOSSL::Aes::process(QByteArray &a) {
    QByteArray buf, fin;

    m_ok = update(a, &buf);
    if (!ok())
        return QByteArray();

    m_ok = final(&fin);
    if (!ok())
        return QByteArray();

    return (buf + fin);
}

int SimpleOSSL::Aes::blockSize() const {
    return EVP_CIPHER_CTX_block_size(&m_context);
}

SimpleOSSL::Aes::~Aes() {
    EVP_CIPHER_CTX_cleanup(&m_context);
}

QByteArray SimpleOSSL::Aes::generateIV() {
    return randomBytes(SIMPLE_OSSL_IV_SIZE);
}

QByteArray SimpleOSSL::Aes::generateKey(int size) {
    return randomBytes(size);
}
