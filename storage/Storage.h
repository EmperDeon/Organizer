#ifndef ORGANIZER_MIO_H
#define ORGANIZER_MIO_H

#include <vars.h>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <storage/SSecure.h>
#include <storage/SMigrations.h>
#include <utils/USingleton.h>
#include "SFiles.h"

class SFiles;

class Storage : public USingleton<Storage> {
    QJsonObject original;
    QJsonArray docs;

    QMap<QString, SFiles *> files;

	SSecure *secure;
    SMigrations *migrations;

public:
	Storage();

	// redirect to original Json
	QJsonValue get(const QString &k) { return original.value(k); }

	QString getS(const QString &k) { return get(k).toString(); }

	bool getB(const QString &k) { return get(k).toBool(); }

	void set(const QString &k, const QJsonValue &v) { original.insert(k, v); }

	void remove(const QString &k) { original.remove(k); }

    QJsonArray getDocs() { return docs; }

    void setDocs(const QJsonArray &doc) { docs = doc; }

    // IO
    void loadJson();

	void saveJson();

    void sendDocsToServer();

    // Docs, TODO: Review, maybe move to separate file
    void loadDocs(QString d);

	QString saveDocs();

    // Files
    void loadFiles(QString f);

    QString saveFiles();


	static SSecure *secureStorage() {
		Storage *st = getInstance();

		return st->secure;
	}

    static SFiles *getFiles(const QString &name);

};

#endif //ORGANIZER_MIO_H
