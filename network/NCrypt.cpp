#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QDebug>
#include <crypt/CRsa.h>
#include "NCrypt.h"

QByteArray NCrypt::encrypt(QByteArray mem, QString path) {
	QJsonObject obj;
	CAes aes(NETWORK_AES_TYPE, getKey(path));

	QString enc = aes.encrypt(QString::fromUtf8(mem)).toUtf8();

	obj["message"] = enc;
	obj["uid"] = st->get("uid");
	obj["sign"] = sign(enc);

	return QJsonDocument(obj).toJson(QJsonDocument::Compact);
}

QByteArray NCrypt::decrypt(QByteArray mes, QString path) {
	QJsonObject obj = QJsonDocument::fromJson(mes).object();

	CAes aes(NETWORK_AES_TYPE, getKey(path));

	if (path.contains("auth/init_network") || path.contains("auth/check_inited")) {
		if (!verify(obj["message"].toString(), obj["sign"].toString())) {
			qWarning() << "Could not verify server response";
		}
	}

	mes = aes.decrypt(obj["message"].toString()).toUtf8();

	return mes;
}

QString NCrypt::getKey(QString path) {
	if (path.contains("auth/init_network") || path.contains("auth/check_inited")) {
		return NETWORK_DEF_KEY;
	}

	return st->getS("net_key");
}

QString NCrypt::sign(QString mes) {
	CRsa rsa(st->getS("rsa_pu"), st->getS("rsa_pr"));

	return rsa.sign(mes);
}

bool NCrypt::verify(QString mes, QString sign) {
	CRsa rsa(st->getS("server_pub"));

	return rsa.verify(mes, sign);
}
