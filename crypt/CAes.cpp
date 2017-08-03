#include "CAes.h"

QString CAes::encrypt(QString message) {
	if (!encryption) {
		encryption = true;
		cipher.setup(QCA::Encode, key, iv);
	}

	return toBase(cipher.process(message.toStdString().c_str()));
}

QString CAes::decrypt(const QString &message) {
	if (encryption) {
		encryption = false;
		cipher.setup(QCA::Decode, key, iv);
	}

	QCA::MemoryRegion mem = cipher.process(fromBase(message));

	return QByteArray(mem.constData());
}

CAes::CAes(QString cipher_name, QString k, QString i) :
		key(fromBase(k)), iv(fromBase(i)), cipher("aes" + cipher_name, QCA::Cipher::CBC, QCA::Cipher::PKCS7) {

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
