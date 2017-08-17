#ifndef ORGANIZER_SSECURE_H
#define ORGANIZER_SSECURE_H


#include <QtCore/QJsonObject>

class SSecure {
	QJsonObject *obj;

public:
	explicit SSecure(QJsonObject *o);

	QString password();

	void initNetworkInfo();
};


#endif //ORGANIZER_SSECURE_H
