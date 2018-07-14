/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <utils/logs/ULogger.h>
#include "CAes.h"
#include "Crypt.h"

CAes::CAes(unsigned int _block_size, const CBytes &_key) :
        block_size(_block_size / 8), key(_key) { // Convert bits to bytes count

    if (block_size % 16 != 0) {
        logW("Block size " + QString::number(block_size) + " is wrong");
    }
}

QString CAes::encrypt(const QString &message) {
    return encryptAr(message.toUtf8()).toBase();
}

CBytes CAes::encryptAr(CBytes message) {
    int err;
    symmetric_CBC cbc;
    CBytes bytes, iv = generateIV();

    addPadding(message);

    if ((err = cbc_start(find_cipher("aes"),
                         iv.data(), bytes_dataI(key), 0,
                         &cbc)) != CRYPT_OK) {
        handle_error(err);
    }

    for (int block_num = 0; block_num < message.size() / block_size; block_num++) {
        CBytes block = message.mid(block_size * block_num, block_size);

        if ((err = cbc_encrypt(block.data(), block.data(),
                               block_size, &cbc)) != CRYPT_OK) {
            handle_error(err);
        }

        bytes += block;
    }

    if ((err = cbc_done(&cbc)) != CRYPT_OK) {
        handle_error(err);
    }

    return iv + bytes;
}

QString CAes::decrypt(const QString &message) {
    return QString::fromUtf8(decryptAr(CBytes(message)).array());
}

CBytes CAes::decryptAr(CBytes message) {
    int err;
    symmetric_CBC cbc;
    CBytes bytes, iv;

    iv = message.mid(0, block_size);
    message.remove(0, block_size);

    if ((err = cbc_start(find_cipher("aes"), iv.data(),
                         bytes_dataI(key), 0,
                         &cbc)) != CRYPT_OK) {
        handle_error(err);
    }

    for (int block_num = 0; block_num < message.size() / block_size; block_num++) {
        CBytes block = message.mid(block_size * block_num, block_size);

        if ((err = cbc_decrypt(block.data(), block.data(),
                               block_size, &cbc)) != CRYPT_OK) {
            handle_error(err);
        }

        bytes += block;
    }

    if ((err = cbc_done(&cbc)) != CRYPT_OK) {
        handle_error(err);
    }

    removePadding(bytes);

    return bytes;
}

void CAes::handle_error(int err) {
    logW(error_to_string(err));
}

CBytes CAes::generateIV() {
    return Crypt::randomBytes(block_size);
}

void CAes::addPadding(CBytes &message) {
    auto append_size = (unsigned char) (block_size - message.size() % block_size);
    message.append(append_size, append_size);
}

void CAes::removePadding(CBytes &message) {
    if (message.size() % block_size != 0) {
        logE("Block is not padded");
        return;
    }

    unsigned char append_size = message.back();
    message.remove(message.sizeI() - append_size, append_size);
}
