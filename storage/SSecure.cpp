/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <crypt/CAes.h>
#include <utils/UPassDialog.h>
#include <crypt/CRsa.h>
#include "SSecure.h"

SSecure::SSecure(QJsonObject *o) : obj(o) {

}

QString SSecure::password() {
    if (!obj->contains("login_hash"))
        obj->insert("login_hash", UPassDialog::getLoginHash(
                obj->value("last_login").toString())); // TODO: Replace with Crypt::deriveKey

    CAes aes(256, obj->value("login_hash").toString());

    QString key;
    key = aes.decrypt(obj->value("doc_key").toString());
    key = Utils::toBase(key.toUtf8());

    return key;
}

void SSecure::initNetworkInfo() {
    obj->insert("uid", Crypt::hash(Crypt::randomBytes(S_UID_SIZE))); // TODO: change to UUID
    obj->insert("net_key", Crypt::randomBytes(NETWORK_AES_KEY_SIZE).toBase());

    CRsa rsa = CRsa::createNew(NETWORK_RSA_KEY_SIZE);
    obj->insert("rsa_pr", rsa.getPrivateKey());
    obj->insert("rsa_pu", rsa.getPublicKey());
}

