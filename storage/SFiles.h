#ifndef ORGANIZER_SFILES_H
#define ORGANIZER_SFILES_H

#include <crypt/CAes.h>
#include <functional>
#include "SFile.h"


class SFiles {
    QString name, key;
    QList<SFile> files;

    CAes aes;

public:
    explicit SFiles(const QString &n, const QString &k, const QJsonArray &fs = {});

    QJsonArray toJson();

    QList<SFile> getFiles() { return files; }

    QString getKey() { return key; }

    void addFile(const QString &file);

    void saveFile(const QString &path, const SFile &file);

    // Static IO functions
    static void moveIn(const QString &f_in, const QString &f_out, const std::function<QByteArray(QByteArray)> &func);

    static void moveOut(const QString &f_in, const QString &f_out, const std::function<QByteArray(QByteArray)> &func);
};


#endif //ORGANIZER_SFILES_H
