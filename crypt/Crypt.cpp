/*
	Copyright (c) 2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <utils/logs/ULogger.h>
#include <vars.h>
#include "Crypt.h"

Crypt::Crypt() {
    if (register_prng(&sprng_desc) != CRYPT_OK) {
        logE("Error registering SPRNG");
    }

    if (register_hash(&sha256_desc) != CRYPT_OK) {
        logE("Error registering SHA256");
    }

    if (register_cipher(&aes_desc) != CRYPT_OK) {
        logE("Error registering AES");
    }

    if (sha256_test() != CRYPT_OK) {
        logE("Self test of SHA256 isn't OK");
    }

    if (rijndael_test() != CRYPT_OK) {
        logE("Self test of AES isn't OK");
    }

    if (sprng_test() != CRYPT_OK) {
        logE("Self test of SPRNG isn't OK");
    }

    if (sprng_start(random_state) != CRYPT_OK) {
        logE("Couldn't initialize SPRNG");
    }

    ltc_mp = ltm_desc;
}

CBytes Crypt::randomBytes(int size) {
    CBytes bytes(size, 0); // Initialize with zeros

    sprng_read(bytes_data(bytes), getInstance()->random_state);

    return bytes;
}

CBytes Crypt::salt() {
    return CBytes::fromBase(CRYPT_DERIVATION_SALT);
}

QString Crypt::hash(CBytes input) {
    CBytes r((int) sha256_desc.hashsize, 0);
    unsigned long r_len;
    int err;

    if ((err = hash_memory(find_hash("sha256"), bytes_data(input), r.data(), &r_len))) {
        logW(error_to_string(err));
    }

    return r.toHex();
}

QString Crypt::hashFile(const QString &filename) {
    CBytes r((int) sha256_desc.hashsize, 0);
    unsigned long r_len;
    int err;

    if ((err = hash_file(find_hash("sha256"), filename.toStdString().c_str(), r.data(), &r_len))) {
        logW(error_to_string(err));
    }

    return r.toHex();
}

CBytes Crypt::deriveKey(const QString &str, int index, int length) {
    CBytes r(length, 0), input(str.toUtf8());
    int err;
    auto out_len = r.size();

    if ((err = pkcs_5_alg2(bytes_data(input), bytes_data(salt()),
                           index + 1, find_hash("sha256"), // Index 0 == Index 1
                           r.data(), &out_len))) {
        logW(error_to_string(err));
    }

    return r;
}
