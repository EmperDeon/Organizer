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
#include <utils/logs/ULogger.h>

Storage::Storage() {
    migrations = new SMigrations;

    checkDir();
    loadJson();
}

void Storage::loadJson() {
    QString json;

    if (QFile::exists(STORAGE_FILE)) {
        logD("Loading " + STORAGE_FILE);

        QFile f(STORAGE_FILE);
        f.open(QFile::ReadOnly);

        json = f.readAll();
    } else {
        logW("Can't open " + STORAGE_FILE);
    }

    original = Utils::fromJson(json);
    original = migrations->processFull(original);

    if (SSettings(this).getB("storage_backup"))
        SBackup::addDocs(json);

    // Here, because needs original json, but decrypt may need access to *secure
    secure = new SSecure(&original);

    loadDocs(original["docs"].toString());

    loaded = true;
    logD("Loaded");
}

void Storage::saveJson() {
    if (!loaded)
        return;

    logD("Saving started");
    WMain *receiver = WMain::getInstance();
    receiver->contr->save();

    original["docs"] = saveDocs();

#ifdef OPTION_SYNC
    if (getB("sync"))
        sendDocsToServer();
#endif

    if (!getB("remember"))
        remove("login_hash");

    QString json = Utils::toJson(original, QJsonDocument::Indented);

    QFile f(STORAGE_FILE);
    if (f.open(QFile::WriteOnly)) {
        f.write(json.toUtf8());
    } else {
        logW("Can't save to " + STORAGE_FILE);
    }

    logD("Saved");
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
        d = QString::fromUtf8(qUncompress(Utils::fromBase(d)));
    }

    docs = Utils::fromJsonA(d);
    docs = migrations->processDocs(docs);
}

QString Storage::saveDocs() {
    QString out = Utils::toJson(docs);

    if (getB("sync")) {
        CAes aes(S_DOC_CIPHER, secure->password());

        out = aes.encrypt(out);
    }

    if (SSettings(this).getB("storage_compress")) {
        out = Utils::toBase(qCompress(out.toUtf8()));
    }

    return out;
}

void Storage::checkDir() {
    QDir root = QDir::root();
    if (!root.exists(STORAGE_DIR)) {
        root.mkdir(STORAGE_DIR);
        logI("Created dir " + STORAGE_DIR);
    }
}
