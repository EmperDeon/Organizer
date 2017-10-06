/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <vars.h>
#include <Qca-qt5/QtCrypto/QtCrypto>
#include "PTabFile.h"

PTabFile::PTabFile(const QJsonObject &o) {
    name = o["name"].toString();
    name_enc = o["name_enc"].toString();
    hash = o["hash"].toString();
    size = o["size"].toString();
    type = o["type"].toString();
}

PTabFile::PTabFile(const QFileInfo &f) {
    name = f.fileName();
    hash = processHash(f);
    size = processSize(f);
    type = processType(f);
}

QJsonObject PTabFile::toJson() {
    return QJsonObject{
            {"name",     name},
            {"name_enc", name_enc},
            {"hash",     hash},
            {"size",     size},
            {"type",     type}
    };
}

QString PTabFile::processHash(const QFileInfo &f) {
    QCA::Hash hash(FILE_HASH);

    QFile f_in(f.absoluteFilePath());
    f_in.open(QFile::ReadOnly);

    QByteArray data;
    do {
        data = f_in.read(FILES_BUFFER_SIZE);
        hash.update(data);
    } while (data.size() != 0);

    return hash.final().toByteArray().toHex();
}

QString PTabFile::processSize(const QFileInfo &f) {
    double size = f.size();
    QString suffix;

    if (size < FILE_KILOBYTE) {
        suffix = "B";

    } else if (size < FILE_MEGABYTE) {
        suffix = "KB";
        size /= FILE_KILOBYTE;

    } else if (size < FILE_GIGABYTE) {
        suffix = "MB";
        size /= FILE_MEGABYTE;

    } else {
        suffix = "GB";
        size /= FILE_GIGABYTE;
    }

    return QString("%1 %2").arg(size, 6, 'f', 2, ' ').arg(suffix);
}

QString PTabFile::processType(const QFileInfo &f) {
    return f.completeSuffix();
}

void PTabFile::processName(CAes &aes) {
    name_enc = aes.encrypt(name);
    name_enc = name_enc.replace('/', '-');
}
