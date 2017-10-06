/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_SFILE_H
#define ORGANIZER_SFILE_H

#include <QtCore/QJsonObject>
#include <QtCore/QFileInfo>
#include <crypt/CAes.h>


class PTabFile {
public:
    QString name, name_enc, hash, size, type;

    explicit PTabFile(const QJsonObject &o);

    explicit PTabFile(const QFileInfo &f);


    static PTabFile fromJson(const QJsonObject &o) { return PTabFile(o); }

    QJsonObject toJson();

    QString processHash(const QFileInfo &f);

    QString processSize(const QFileInfo &f);

    QString processType(const QFileInfo &f);

    void processName(CAes &aes);
};

#endif //ORGANIZER_SFILE_H
