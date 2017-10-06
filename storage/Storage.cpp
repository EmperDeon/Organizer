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

    // Check if storage file is encrypted
	if (!json.startsWith('{')) {
        CAes fileAes(STORAGE_CIPHER, STORAGE_KEY);

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

#ifdef OPTION_SYNC
	if (getB("sync"))
		sendDocsToServer();
#endif

	if (!getB("remember"))
		remove("login_hash");

	QString json = CTools::toJson(original, QJsonDocument::Indented);

// Encrypt output ?
#ifdef ENCRYPT_OUT
    CAes aes(STORAGE_CIPHER, STORAGE_KEY);
    json = aes.encrypt(json);
#endif

	QFile f(STORAGE_FILE);
	f.open(QFile::WriteOnly);
	f.write(json.toUtf8());
	f.close();
}

void Storage::sendDocsToServer() {
    QString docs = saveDocs();

    Network net;
    net.request("documents/save", {{"docs", docs}});
}

void Storage::loadDocs(QString d) {
	if (getB("sync")) { // Decrypt
        CAes aes(S_DOC_CIPHER, secure->password());

		d = aes.decrypt(d);
	}

    if (getB("is_compress")) {
        d = QString::fromUtf8(qUncompress(CTools::fromBase(d).toByteArray()));
    }

	docs = CTools::fromJsonA(d);
	docs = migrations->processDocs(docs);
}

QString Storage::saveDocs() {
    QString out = CTools::toJson(docs);

	if (getB("sync")) {
        CAes aes(S_DOC_CIPHER, secure->password());

        out = aes.encrypt(out);
    }

    if (getB("is_compress")) {
        out = CTools::toBase(qCompress(out.toUtf8()));
    }

    return out;
}