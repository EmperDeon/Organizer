#include <QtCore/QDir>
#include <vars.h>
#include "CFiles.h"
#include "CAes.h"
#include <QDebug>
#include <QtCore/QDataStream>

void CFiles::copyToEncryptedStorage(const QString &path, const QString &file) {
    QDir dir;
    dir.mkpath(FILES_DIR);
    dir.cd(FILES_DIR);
    dir.mkpath(path);
    dir.cd(path);

    QFileInfo f_info(file);

    QByteArray read_data, write_data;

    QFile f_in(file), f_out(dir.filePath(f_info.fileName()));

    f_in.open(QFile::ReadOnly);
    f_out.open(QFile::WriteOnly);

    QDataStream s_out(&f_out);
    s_out.setVersion(QDataStream::Qt_5_0);

    do {
        read_data = f_in.read(FILES_BUFFER_SIZE);

        write_data = process(Encrypt, read_data);

        s_out << write_data.size();
        s_out << write_data;
    } while (read_data.size() != 0);

    f_in.close();
    f_out.close();
}

void CFiles::copyFromEncryptedStorage(const QString &path, const QString &file, const QString &save_path) {
    QDir dir(FILES_DIR);
    dir.cd(path);

    QFileInfo f_info(file);

    QByteArray read_data, write_data;

    QFile f_in(dir.filePath(f_info.fileName())), f_out(QDir(save_path).filePath(f_info.fileName()));

    f_in.open(QFile::ReadOnly);
    f_out.open(QFile::WriteOnly);

    int block_size;
    QDataStream s_in(&f_in);
    s_in.setVersion(QDataStream::Qt_5_0);

    do {
        s_in >> block_size;
        qDebug() << block_size;
        s_in.skipRawData(4);

        auto *block = new char[block_size];
        s_in.readRawData(block, block_size);

        read_data = QByteArray::fromRawData(block, block_size);


        write_data = process(Decrypt, read_data);

        f_out.write(write_data);
    } while (read_data.size() != 0);

    f_in.close();
    f_out.close();
}

QByteArray CFiles::process(CFiles::Type type, const QByteArray &data) {
    CAes aes("128", "+7QqHqbuJEursfbU+uaJUmN1obOcZEza3oRUtmS+Qz8=");

    switch (type) {
        case Encrypt:
            return aes.encryptAr(data);
        case Decrypt:
            return aes.decryptAr(data);
    }
}
