/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <crypt/CAes.h>
#include <utils/UPassDialog.h>
#include <crypt/CRsa.h>
#include "SSecure.h"

QString SSecure::password() {
    if (!obj.contains("login_hash"))
        obj["login_hash"] = UPassDialog::getLoginHash(obj["last_login"]); // TODO: Replace with Crypt::deriveKey

    CAes aes(256, obj["login_hash"]);

    QString key;
    key = aes.decrypt(obj["doc_key"]);
    key = Utils::toBase(key.toUtf8());

    return key;
}

void SSecure::initNetworkInfo() {
    obj["uid"] = Crypt::hash(Crypt::randomBytes(S_UID_SIZE)); // TODO: change to UUID
    obj["net_key"] = Crypt::randomBytes(NETWORK_AES_KEY_SIZE).toBase();

    CRsa rsa = CRsa::generatePrivate(NETWORK_RSA_KEY_SIZE);
    obj["rsa_pr"] = rsa.privateKey();
    obj["rsa_pu"] = rsa.publicKey();
}
