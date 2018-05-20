/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtCore/QDir>
#include <QtCore/QDataStream>
#include <widgets/files/WFiles.h>
#include <QDebug>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMessageBox>
#include <utils/logs/ULogger.h>
#include <vendor/simple_ossl/include/simple_ossl.h>

PTabFiles::PTabFiles() {
    w_files = new WFiles(this);
}

void PTabFiles::addFile(const QString &file) {
    QDir dir;

    logI("Adding file");

    dir.mkpath(FILES_DIR);
    dir.cd(FILES_DIR);
    dir.mkpath(name);
    dir.cd(name);

    PTabFile s_file(file);
    s_file.processName(*aes);

    int existing_file = findFileByName(s_file.name);

    if (existing_file != -1) {
        if (QMessageBox::question(w_files, QObject::tr("File adding"),
                                  QObject::tr("Are you sure you want to overwrite existing file ?")) ==
            QMessageBox::No) {
            return;
        }
    }

    logD(QString("Copying and encrypting file %1 to %2").arg(file).arg(dir.relativeFilePath(s_file.name_enc)));

    PTabFiles::moveIn(file, dir.filePath(s_file.name_enc), [this](QByteArray in) {
        return this->aes->encryptAr(in);
    });

    if (existing_file == -1) {
        files << s_file;

    } else {
        files[existing_file] = s_file;
    }
}

void PTabFiles::saveFile(const QString &path, const PTabFile &file) {
    QDir dir(FILES_DIR);
    dir.cd(name);

    const QString &f_in = dir.filePath(file.name_enc);
    const QString &f_out = QDir(path).filePath(file.name);

    logD(QString("Copying and decryptind file %1 to %2").arg(f_in).arg(f_out));

    PTabFiles::moveOut(f_in, f_out, [this](QByteArray in) {
        return this->aes->decryptAr(in);
    });
}

// TODO: Review
void PTabFiles::moveIn(const QString &f_in, const QString &f_out, const std::function<QByteArray(QByteArray)> &func) {
    QByteArray read_data, write_data;
    QFile in(f_in), out(f_out);

    if (!in.open(QFile::ReadOnly)) {
        logE("Could not open file for read");
        logV(f_in);
        return;
    }

    if (!out.open(QFile::WriteOnly)) {
        logE("Couldn't open file for write");
        logV(f_out);
        return;
    }

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

void PTabFiles::moveOut(const QString &f_in, const QString &f_out, const std::function<QByteArray(QByteArray)> &func) {
    int block_size;
    QByteArray read_data, write_data;
    QFile in(f_in), out(f_out);

    if (!in.open(QFile::ReadOnly)) {
        logE("Could not open file for read");
        logV(f_in);
        return;
    }

    if (!out.open(QFile::WriteOnly)) {
        logE("Couldn't open file for write");
        logV(f_out);
        return;
    }

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

int PTabFiles::findFileByName(const QString &f) {
    for (int i = 0; i < files.size(); i++) {
        if (files[i].name == f)
            return i;
    }

    return -1;
}

void PTabFiles::del(const PTabFile &file) {
    int i = findFileByName(file.name);

    if (i != -1) {
        QDir dir(FILES_DIR);
        dir.cd(name);
        dir.remove(file.name_enc);

        files.removeAt(i);
    }
}

void PTabFiles::rename(const PTabFile &file) {
    int i = findFileByName(file.name);

    if (i != -1) {
        files[i].name = QInputDialog::getText(w_files, QObject::tr("Enter new name for file"), QObject::tr("Name: "),
                                              QLineEdit::Normal, files[i].name);
    }
}

void PTabFiles::initIfNeeded(MTab *tab, const QJsonObject &o) {
    if (o["files_name"].toString().isEmpty()) {
        auto &ob = const_cast<QJsonObject &>(o);

        ob["files_name"] = Utils::hash(tab->desc());
        ob["file_key"] = Utils::toBase(SimpleOSSL::Aes::generateKey(FILES_KEY_SIZE));
        ob["files"] = QJsonArray();
    }
}

void PTabFiles::readInfo(const QJsonObject &o) {
    name = o["files_name"].toString();
    key = o["file_key"].toString();

    files.clear();
    for (auto v : o["files"].toArray()) {
        files << PTabFile(v.toObject());
    }

    delete aes;
    aes = new CAes(FILES_CIPHER, key);

    w_files->updateFileList();
}

void PTabFiles::writeInfo(QJsonObject &o) {
    QJsonArray ar;
    for (auto f : files) {
        ar << f.toJson();
    }

    o["files"] = ar;
}

QWidget *PTabFiles::getWidget() {
    return w_files;
}
