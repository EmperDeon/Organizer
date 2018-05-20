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

#include <openssl/rand.h>
#include "include/Utils.h"

QByteArray SimpleOSSL::bio2buf(BIO *b) {
    QByteArray buf;
    while (true) {
        QByteArray block(1024, 0);
        int ret = BIO_read(b, block.data(), block.size());
        if (ret <= 0)
            break;
        block.resize(ret);
        buf.append(block);
        if (ret != 1024)
            break;
    }
    BIO_free(b);
    return buf;
}

static int enhex(uchar c) {
    if (c < 10)
        return c + '0';
    else if (c < 16)
        return c - 10 + 'a';
    else
        return -1;
}

static int dehex(char c) {
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    else if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    else if (c >= '0' && c <= '9')
        return c - '0';
    else
        return -1;
}

QByteArray SimpleOSSL::toHex(QByteArray a) {
    QByteArray out(a.size() * 2, 0);
    int at = 0, c;
    bool _ok = true;

    for (const auto &n : a) {
        uchar lo = (uchar) n & 0x0f;
        uchar hi = (uchar) n >> 4;
        c = enhex(hi);
        if (c == -1) {
            _ok = false;
            break;
        }
        out[at++] = (char) c;
        c = enhex(lo);
        if (c == -1) {
            _ok = false;
            break;
        }
        out[at++] = (char) c;
    }
    if (!_ok)
        return QByteArray();

    return out;
}

QByteArray SimpleOSSL::fromHex(QByteArray a) {
    uchar lo = 0, hi = 0;
    bool flag = false, _ok = true;

    QByteArray out(a.size() / 2, 0);
    int at = 0, c;
    for (const auto &n : a) {
        c = dehex((char) n);
        if (c == -1) {
            _ok = false;
            break;
        }

        if (flag) {
            lo = (uchar) c;
            uchar full = ((hi & 0x0f) << 4) + (lo & 0x0f);
            out[at++] = full;
            flag = false;
        } else {
            hi = (uchar) c;
            flag = true;
        }
    }

    if (flag || !_ok)
        return QByteArray();

    return out;
}

QByteArray SimpleOSSL::randomBytes(int size) {
    QByteArray buf(size, 0);
    int r;
    // FIXME: loop while we don't have enough random bytes.
    while (true) {
        r = RAND_bytes((unsigned char *) (buf.data()), size);
        if (r == 1) break; // success
        r = RAND_pseudo_bytes((unsigned char *) (buf.data()), size);
        if (r >= 0) break; // accept insecure random numbers
    }
    return buf;
}

QString SimpleOSSL::toBase64(const QByteArray &a) {
    return QString::fromLatin1(a.toBase64());
}

QByteArray SimpleOSSL::fromBase64(const QString &s) {
    return QByteArray::fromBase64(s.toLatin1());
}
