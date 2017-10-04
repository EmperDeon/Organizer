#include <QtCore/QDir>
#include <QtCore/QDataStream>
#include "SFiles.h"

SFiles::SFiles(const QString &n, const QString &k, const QJsonArray &fs) : name(n), key(k), aes(FILES_CIPHER, key) {
    for (auto v : fs) {
        files << SFile::fromJson(v.toObject());
    }
}

QJsonArray SFiles::toJson() {
    QJsonArray r;

    for (auto f : files) {
        r << f.toJson();
    }

    return r;
}

void SFiles::addFile(const QString &file) {
    QDir dir;

    dir.mkpath(FILES_DIR);
    dir.cd(FILES_DIR);
    dir.mkpath(name);
    dir.cd(name);

    SFile s_file(file);
    s_file.processName(aes);


    SFiles::moveIn(s_file.name, dir.filePath(s_file.name_enc), [this](QByteArray in) {
        return this->aes.encryptAr(in);
    });

    files << s_file;

//    QByteArray read_data, write_data;
//    QFile f_in(s_file.name), f_out(dir.filePath(s_file.name_enc));
//
//    f_in.open(QFile::ReadOnly);
//    f_out.open(QFile::WriteOnly);
//
//    QDataStream s_out(&f_out);
//    s_out.setVersion(QDataStream::Qt_5_0);
//
//    do {
//        read_data = f_in.read(FILES_BUFFER_SIZE);
//
//        write_data = aes.encryptAr(read_data);
//
//        s_out << write_data.size();
//        s_out << write_data;
//    } while (read_data.size() != 0);
//
//    f_in.close();
//    f_out.close();
}

void SFiles::saveFile(const QString &path, const SFile &file) {
    QDir dir(FILES_DIR);
    dir.cd(name);

    const QString &f_in = dir.filePath(file.name_enc);
    const QString &f_out = QDir(path).filePath(file.name);

    SFiles::moveOut(f_in, f_out, [this](QByteArray in) {
        return this->aes.decryptAr(in);
    });

//    QByteArray read_data, write_data;
//
//    QFile f_in(dir.filePath(f_info.fileName())), f_out(QDir(save_path).filePath(f_info.fileName()));
//
//    f_in.open(QFile::ReadOnly);
//    f_out.open(QFile::WriteOnly);
//
//    int block_size;
//    QDataStream s_in(&f_in);
//    s_in.setVersion(QDataStream::Qt_5_0);
//
//    do {
//        s_in >> block_size;
//        s_in.skipRawData(4);
//
//        auto *block = new char[block_size];
//        s_in.readRawData(block, block_size);
//
//        read_data = QByteArray::fromRawData(block, block_size);
//
//
//        write_data = aes.decryptAr(read_data);
//
//        f_out.write(write_data);
//    } while (read_data.size() != 0);
//
//    f_in.close();
//    f_out.close();
}

void SFiles::moveIn(const QString &f_in, const QString &f_out, const std::function<QByteArray(QByteArray)> &func) {
    QByteArray read_data, write_data;
    QFile in(f_in), out(f_out);

    in.open(QFile::ReadOnly);
    out.open(QFile::WriteOnly);

    QDataStream s_out(&out);
    s_out.setVersion(QDataStream::Qt_5_0);

    do {
        read_data = in.read(FILES_BUFFER_SIZE);

        write_data = func(read_data);

        s_out << write_data.size();
        s_out << write_data;
    } while (read_data.size() != 0);

    in.close();
    out.close();
}

void SFiles::moveOut(const QString &f_in, const QString &f_out, const std::function<QByteArray(QByteArray)> &func) {
    int block_size;
    QByteArray read_data, write_data;
    QFile in(f_in), out(f_out);

    in.open(QFile::ReadOnly);
    out.open(QFile::WriteOnly);

    QDataStream s_in(&in);
    s_in.setVersion(QDataStream::Qt_5_0);

    do {
        s_in >> block_size;
        s_in.skipRawData(4);

        auto *block = new char[block_size];
        s_in.readRawData(block, block_size);

        read_data = QByteArray::fromRawData(block, block_size);

        write_data = func(read_data);

        out.write(write_data);
    } while (read_data.size() != 0);

    in.close();
    out.close();
}
