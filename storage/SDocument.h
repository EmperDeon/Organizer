#ifndef ORGANIZER_SDOCUMENT_H
#define ORGANIZER_SDOCUMENT_H

#include <QtCore/QJsonObject>

class SDocument : public QJsonObject {
public:
	explicit SDocument(QJsonObject o);

	QList<QJsonObject> getDocs();
};


#endif //ORGANIZER_SDOCUMENT_H
