#include <crypt/CAes.h>
#include <utils/UPassDialog.h>
#include <crypt/CRsa.h>
#include "SSecure.h"

SSecure::SSecure(QJsonObject *o) : obj(o) {

}

QString SSecure::password() {
	if (!obj->contains("login_hash"))
		obj->insert("login_hash", UPassDialog::getLoginHash(obj->value("last_login").toString()));

	CAes aes("256", obj->value("login_hash").toString());

	QString key;
	key = aes.decrypt(obj->value("doc_key").toString());
	key = CAes::createKey(key);

	return key;
}

void SSecure::initNetworkInfo() {
	QString rsa_pr;

	obj->insert("uid", CTools::hash(CTools::randomStr(S_UID_SIZE)));
	obj->insert("net_key", CAes::createKey(NETWORK_AES_KEY_SIZE));

	rsa_pr = CRsa::createPrivateKey(NETWORK_RSA_KEY_SIZE);
	obj->insert("rsa_pr", rsa_pr);
	obj->insert("rsa_pu", CRsa::createPublicKey(rsa_pr));
}

void SSecure::initNewLogin() {
	obj->insert("login_hash", UPassDialog::getLoginHash(obj->value("last_login").toString()));
	obj->insert("login_date", QDateTime::currentSecsSinceEpoch());
}

void SSecure::clearLoginInfo() {
	obj->remove("login_hash");
	obj->remove("login_date");

	obj->remove("doc_key");
}
