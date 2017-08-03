#include "NAuth.h"

NAuth::NAuth() {
	storage = Storage::getInstance();
	secure = storage->secureStorage();
}

void NAuth::newRegister() {
	secure->initNewLogin();

	QString key = CAes::createKey(S_DOC_KEY_SIZE);
	CAes aes("256", storage->getS("login_hash"));
	storage->set("doc_key", aes.encrypt(key));

	QJsonObject o = netw.request("auth/register", {
			{"login", storage->getS("login_hash")},
			{"key",   storage->getS("doc_key")}
	}).toObject();

	if (o["status"].toString() == "reg_ok") {
		storage->set("token", o["token"]);
		storage->set("sync", true);
	}
}
