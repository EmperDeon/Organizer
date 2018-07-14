/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <utils/logs/ULogger.h>
#include "CRsa.h"
#include "utils/Utils.h"
#include "Crypt.h"
#include <QDebug>

#define RSA_INIT int err, stat; \
                 CBytes r(8192, (char)0); \
                 unsigned long r_len;

CRsa::CRsa(rsa_key *_key) : key(_key) {}

CRsa::CRsa(const QString &_key, bool _private) {
    int err;
    CBytes in;

    if (_key.isEmpty()) {
        logE("No key is supplied");
        return;
    }

    if (_private) {
        in = CBytes::fromBase(_key.mid(28, _key.size() - 54));
    } else {
        in = CBytes::fromBase(_key.mid(27, _key.size() - 52));
    }

    key = new rsa_key;
    if ((err = rsa_import(bytes_data(in), key)) != CRYPT_OK) {
        logE(error_to_string(err));
    }
}

QString CRsa::encode(QString str) {
    if (key == nullptr)
        return "";

    CBytes in(str.toUtf8());
    RSA_INIT

    if ((err = rsa_encrypt_key_ex(bytes_data(in), r.data(), &r_len,
                                  nullptr, 0, RSA_PRNG, RSA_HASH,
                                  LTC_PKCS_1_OAEP, key)) != CRYPT_OK) {
        logE(error_to_string(err));
    }

    return r.left(r_len).toBase();
}

QString CRsa::decode(QString str) {
    if (key == nullptr)
        return "";

    CBytes in(str);
    RSA_INIT

    if ((err = rsa_decrypt_key_ex(bytes_data(in), r.data(), &r_len,
                                  nullptr, 0, RSA_HASH,
                                  LTC_PKCS_1_OAEP, &stat, key)) != CRYPT_OK) {
        logE(error_to_string(err));
    }

    return QString::fromUtf8(r.left(r_len).array());
}

QString CRsa::sign(QString str) {
    if (key == nullptr)
        return "";

    CBytes in = CBytes::fromHex(Crypt::hash(str));
    RSA_INIT

    if ((err = rsa_sign_hash_ex(bytes_data(in), r.data(), &r_len,
                                LTC_PKCS_1_V1_5, nullptr, 0,
                                RSA_HASH, 8, key)) != CRYPT_OK) {
        logE(error_to_string(err));
    }

    return r.left(r_len).toBase();
}

bool CRsa::verify(QString str, QString sig) {
    if (key == nullptr)
        return false;

    CBytes hash = CBytes::fromHex(Crypt::hash(str)),
            in = CBytes(sig);
    RSA_INIT

    if ((err = rsa_verify_hash_ex(bytes_data(in), bytes_data(hash),
                                  LTC_PKCS_1_V1_5, RSA_HASH,
                                  8, &stat, key)) != CRYPT_OK) {
        logE(error_to_string(err));
    }

    return stat == 1;
}

QString CRsa::privateKey() {
    if (key == nullptr)
        return "";

    RSA_INIT

    if ((err = rsa_export(r.data(), &r_len, PK_PRIVATE, key)) != CRYPT_OK) {
        logE(error_to_string(err));
    }

    return "-----BEGIN PRIVATE KEY-----\n" + r.left(r_len).toBase() + "\n-----END PRIVATE KEY-----";
}

QString CRsa::publicKey() {
    if (key == nullptr)
        return "";

    RSA_INIT

    if ((err = rsa_export(r.data(), &r_len, PK_PUBLIC, key)) != CRYPT_OK) {
        logE(error_to_string(err));
    }

    return "-----BEGIN PUBLIC KEY-----\n" + r.left(r_len).toBase() + "\n-----END PUBLIC KEY-----";
}

CRsa::~CRsa() {
    if (key != nullptr)
        rsa_free(key);
}

CRsa CRsa::generatePrivate(int size) {
    int err;
    auto *key = new rsa_key;

    if ((err = rsa_make_key(RSA_PRNG, size / 8, 65537, key)) != CRYPT_OK) {
        logE(error_to_string(err));
    }

    return CRsa(key);
}
