/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <vendor/additions.h>
#include <QtCore/QJsonDocument>
#include <QtCore/QDebug>
#include <crypt/CRsa.h>
#include "NCrypt.h"

QByteArray NCrypt::encrypt(QByteArray mem, QString path) {
    json_o obj;
	CAes aes(NETWORK_AES_TYPE, getKey(path));

	QString enc = aes.encrypt(QString::fromUtf8(mem)).toUtf8();

	obj["message"] = enc;
	obj["uid"] = st->get("uid");
	obj["sign"] = sign(enc);

    return obj.dumpQ().toUtf8();
}

QByteArray NCrypt::decrypt(QByteArray mes, QString path) {
    json_o obj = json::parse(QString::fromUtf8(mes).toStdString());

	CAes aes(NETWORK_AES_TYPE, getKey(path));

	if (path.contains("auth/init_network") || path.contains("auth/check_inited")) {
        if (!verify(obj["message"], obj["sign"])) {
			qWarning() << "Could not verify server response";
		}
	}

    mes = aes.decrypt(obj["message"]).toUtf8();

	return mes;
}

QString NCrypt::getKey(QString path) {
	if (path.contains("auth/init_network") || path.contains("auth/check_inited")) {
		return NETWORK_DEF_KEY;
	}

	return st->getS("net_key");
}

QString NCrypt::sign(QString mes) {
    CRsa rsa(st->getS("rsa_pr"), true);

	return rsa.sign(mes);
}

bool NCrypt::verify(QString mes, QString sign) {
	CRsa rsa(st->getS("server_pub"));

	return rsa.verify(mes, sign);
}
