#ifndef ORGANIZER_MIO_H
#define ORGANIZER_MIO_H

#include <vars.h>
#include <QtCore/QJsonObject>
#include <storage/SDocument.h>
#include <storage/SSecure.h>

class Storage {
	QJsonObject original, docs;

	SSecure *secure;

public:
	Storage();

	// redirect to original Json
	QJsonValue get(const QString &k) { return original.value(k); }

	QString getS(const QString &k) { return get(k).toString(); }

	bool getB(const QString &k) { return get(k).toBool(); }

	void set(const QString &k, const QJsonValue &v) { original.insert(k, v); }

	void remove(const QString &k) { original.remove(k); }

	SDocument *getDocument(const QString &k) { return new SDocument(docs[k].toObject()); }

	void saveDocument(const QString &k, const QJsonObject &doc) { docs[k] = doc; }

	void loadJson();

	void saveJson();

	void loadDocs(QString d);

	QString saveDocs();

	// Singleton
	static Storage *getInstance() {
		static Storage *instance = nullptr;

		if (instance == nullptr) {
			instance = new Storage;
		}

		return instance;
	}

	static SSecure *secureStorage() {
		Storage *st = getInstance();

		return st->secure;
	}

	void sendDocsToServer();
};

#endif //ORGANIZER_MIO_H
