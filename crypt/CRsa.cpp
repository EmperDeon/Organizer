#include "CRsa.h"
#include "CTools.h"
#include <QDebug>

CRsa::CRsa(QString pub, QString prv, QString passphrase) {
	publicKey = QCA::PublicKey::fromPEM(pub);


	if (prv != "")
		privateKey = QCA::PrivateKey::fromPEM(prv, passphrase.toStdString().c_str());

}

QString CRsa::createPrivateKey(int size) {
	QCA::PrivateKey privateKey = QCA::KeyGenerator().createRSA(size);

	return privateKey.toPEM();
}

QString CRsa::createPublicKey(QString private_key) {
	QCA::PrivateKey privateKey = QCA::PrivateKey::fromPEM(private_key);

	return privateKey.toPublicKey().toPEM();
}

QString CRsa::encode(QString str) {
	QCA::SecureArray mem = publicKey.encrypt(str.toStdString().c_str(), QCA::EME_PKCS1v15);
	return CTools::toBase(mem);
}

QString CRsa::decode(QString str) {
	QCA::SecureArray mem;
	privateKey.decrypt(CTools::fromBase(str), &mem, QCA::EME_PKCS1v15);

	return QByteArray(mem.constData());
}


QString CRsa::sign(QString str) {
	QByteArray mem = privateKey.signMessage(str.toStdString().c_str(), RSA_SIGN_ALG);

	return CTools::toBase(mem);
}

bool CRsa::verify(QString str, QString sig) {
	return publicKey.canVerify() &&
	       publicKey.verifyMessage(str.toStdString().c_str(), CTools::fromBase(sig).toByteArray(), RSA_SIGN_ALG);
}


QString CRsa::getPrivateKey() {
	return privateKey.toPEM();
}

QString CRsa::getPublicKey() {
	return publicKey.toPEM();
}
