#ifndef ORGANIZER_NCRYPT_H
#define ORGANIZER_NCRYPT_H

#include <crypt/CAes.h>
#include <storage/Storage.h>

class NCrypt {
	Storage *st;

public:
	NCrypt() : st(Storage::getInstance()) {}

	QByteArray encrypt(QByteArray mem, QString path);

	QByteArray decrypt(QByteArray mes, QString path, bool ver = true);

	QString getKey(QString path);

	QString sign(QString mes);

	bool verify(QString mes, QString sign);
};


#endif //ORGANIZER_NCRYPT_H
