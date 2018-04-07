/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <crypt/CAes.h>
#include "Storage.h"
#include "SBackup.h"
#include <utils/UPassDialog.h>
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
    if (!(json.isEmpty() || json.startsWith('{'))) {
        CAes fileAes(STORAGE_CIPHER, STORAGE_KEY);

        json = fileAes.decrypt(json);
    }

    original = CTools::fromJson(json);
    original = migrations->processFull(original);

    if (SSettings(this).getB("storage_backup"))
        SBackup::addDocs(json);

    // Here, because needs original json, but decrypt may need access to *secure
    secure = new SSecure(&original);

    loadDocs(original["docs"].toString());

    loaded = true;
}

void Storage::saveJson() {
    if (!loaded)
        return;

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
    if (SSettings(this).getB("storage_encrypt")) {
        CAes aes(STORAGE_CIPHER, STORAGE_KEY);
        json = aes.encrypt(json);
    }


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

    if (SSettings(this).getB("storage_compress")) {
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

    if (SSettings(this).getB("storage_compress")) {
        out = CTools::toBase(qCompress(out.toUtf8()));
    }

    return out;
}
