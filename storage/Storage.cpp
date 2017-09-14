#include <crypt/CAes.h>
#include "Storage.h"
#include <utils/UPassDialog.h>
#include <QtCore/QFile>
#include <QDebug>
#include <network/Network.h>
#include <widgets/WMain.h>

Storage::Storage() {
	migrations = new SMigrations;

	loadJson();
}

void Storage::loadJson() {
	QFile f(STORAGE_FILE);

	if (!f.open(QFile::ReadOnly)) {
		qWarning() << QString("Can't open ") + STORAGE_FILE;
	}

	QString json = f.readAll();

	if (!json.startsWith('{')) {
		CAes fileAes("128", STORAGE_KEY);

		json = fileAes.decrypt(json);
	}

	original = CTools::fromJson(json);
	original = migrations->processFull(original);

	// Here, because needs original json, but decrypt may need access to *secure
	secure = new SSecure(&original);

	loadDocs(original["docs"].toString());
}

void Storage::saveJson() {
	WMain *receiver = WMain::getInstance();
    receiver->contr->save();

    original["docs"] = saveDocs();

	if (getB("sync"))
		sendDocsToServer();

	if (!getB("remember"))
		remove("login_hash");

	QString json = CTools::toJson(original, QJsonDocument::Indented);

// Encrypt output ?
#ifdef ENCRYPT_OUT
	CAes aes("128", STORAGE_KEY);
	json = aes.encrypt(json);
#endif

	QFile f(STORAGE_FILE);
	f.open(QFile::WriteOnly);
	f.write(json.toUtf8());
	f.close();
}

void Storage::loadDocs(QString d) {
	if (getB("sync")) { // Decrypt
		CAes aes("128", secure->password());

		d = aes.decrypt(d);
	}

	docs = CTools::fromJsonA(d);
	docs = migrations->processDocs(docs);
}

QString Storage::saveDocs() {
	QString doc = CTools::toJson(docs);

	if (getB("sync")) {
		CAes aes("128", secure->password());

		doc = aes.encrypt(doc);
	}

	return doc;
}

void Storage::sendDocsToServer() {
	QString docs = saveDocs();

	Network net;
	net.request("documents/save", {{"docs", docs}});
}
