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

#include "include/Hash.h"

SimpleOSSL::Hash::Hash(const EVP_MD *algorithm) {
    m_algorithm = algorithm;
    EVP_DigestInit(&m_context, m_algorithm);
}

SimpleOSSL::Hash::~Hash() {
    EVP_MD_CTX_cleanup(&m_context);
}

void SimpleOSSL::Hash::clear() {
    EVP_MD_CTX_cleanup(&m_context);
    EVP_DigestInit(&m_context, m_algorithm);
}

void SimpleOSSL::Hash::update(const QByteArray &a) {
    EVP_DigestUpdate(&m_context, (unsigned char *) a.data(), static_cast<size_t>(a.size()));
}

QByteArray SimpleOSSL::Hash::final() {
    QByteArray a(EVP_MD_size(m_algorithm), 0);
    EVP_DigestFinal(&m_context, (unsigned char *) a.data(), nullptr);
    return a;
}

QByteArray SimpleOSSL::Hash::process(const QByteArray &a) {
    clear();
    update(a);
    return final();
}

QString SimpleOSSL::Hash::hashToString(const QByteArray &a) {
    return QString::fromLatin1(toHex(process(a)));
}
