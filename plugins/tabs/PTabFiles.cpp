#include <QtCore/QDir>
#include <QtCore/QDataStream>
#include <widgets/files/WFiles.h>
#include <QDebug>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMessageBox>

PTabFiles::PTabFiles() {
    w_files = new WFiles(this);
}

void PTabFiles::addFile(const QString &file) {
    QDir dir;

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
            qDebug() << "no";

            return;
        }
    }

    PTabFiles::moveIn(file, dir.filePath(s_file.name_enc), [this](QByteArray in) {
        return this->aes->encryptAr(in);
    });

    if (existing_file == -1) {
        files << s_file;

    } else {
        files[existing_file] = s_file;
    }

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

void PTabFiles::saveFile(const QString &path, const PTabFile &file) {
    QDir dir(FILES_DIR);
    dir.cd(name);

    const QString &f_in = dir.filePath(file.name_enc);
    const QString &f_out = QDir(path).filePath(file.name);

    PTabFiles::moveOut(f_in, f_out, [this](QByteArray in) {
        return this->aes->decryptAr(in);
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

void PTabFiles::moveIn(const QString &f_in, const QString &f_out, const std::function<QByteArray(QByteArray)> &func) {
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

void PTabFiles::moveOut(const QString &f_in, const QString &f_out, const std::function<QByteArray(QByteArray)> &func) {
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

        ob["files_name"] = CTools::hash(tab->getDesc());
        ob["file_key"] = CAes::createKey(FILES_KEY_SIZE);
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
