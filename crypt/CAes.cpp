/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "CAes.h"

QString CAes::encrypt(QString message) {
    return toBase(encryptAr(message.toStdString().c_str()));
}

QByteArray CAes::encryptAr(QByteArray message) {
    if (!encryption) {
        encryption = true;
        cipher.setup(QCA::Encode, key, iv);
    }

    return cipher.process(message).toByteArray();
}

QString CAes::decrypt(const QString &message) {
    return decryptAr(fromBase(message).toByteArray());
}

QByteArray CAes::decryptAr(const QByteArray &message) {
    if (encryption) {
        encryption = false;
        cipher.setup(QCA::Decode, key, iv);
    }

    QCA::MemoryRegion mem = cipher.process(message);

    return mem.toByteArray();
}


CAes::CAes(QString cipher_name, QString k, QString i) :
        key(fromBase(k)), iv(fromBase(i)), cipher("aes" + cipher_name, AES_MODE, AES_PADDING) {

    encryption = true;
    cipher.setup(QCA::Encode, key, iv);
}

QString CAes::createKey(int key_size) {
    QCA::SymmetricKey key(key_size);

    return toBase(key);
}

QString CAes::createKey(QString k) {
    return toBase(k.toStdString().c_str());
}

QString CAes::createIV() {
    QCA::InitializationVector iv(16);

    return toBase(iv);
}