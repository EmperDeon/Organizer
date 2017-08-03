#include <QtCore/QList>
#include "SDocument.h"

SDocument::SDocument(QJsonObject o) : QJsonObject(o) {

}

QList<QJsonObject> SDocument::getDocs() {
	QList<QJsonObject> r;
	for (const QString &v: keys()) {
		r << value(v).toObject();
	}

	return r;
}