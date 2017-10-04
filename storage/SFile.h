#ifndef ORGANIZER_SFILE_H
#define ORGANIZER_SFILE_H

#include <QtCore/QJsonObject>
#include <QtCore/QFileInfo>
#include <crypt/CAes.h>


class SFile {
public:
    QString name, name_enc, hash, size, type;

    explicit SFile(const QJsonObject &o);

    explicit SFile(const QFileInfo &f);


    static SFile fromJson(const QJsonObject &o) { return SFile(o); }

    QJsonObject toJson();

    QString processHash(const QFileInfo &f);

    QString processSize(const QFileInfo &f);

    QString processType(const QFileInfo &f);

    void processName(CAes &aes);
};

#endif //ORGANIZER_SFILE_H
