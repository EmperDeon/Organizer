#ifndef ORGANIZER_SFILES_H
#define ORGANIZER_SFILES_H

#include <crypt/CAes.h>
#include <functional>
#include <plugins/tabs/PTabPlugin.h>
#include <widgets/files/WFiles.h>
#include <tabs/MTab.h>
#include "PTabFile.h"

class WFiles;


class PTabFiles : public PTabPlugin {
    QString name, key;
    QList<PTabFile> files;

    CAes *aes = nullptr;

    WFiles *w_files;

public:
    PTabFiles();

    QList<PTabFile> getFiles() { return files; }

    void addFile(const QString &file);

    void saveFile(const QString &path, const PTabFile &file);

    // Static IO functions
    static void moveIn(const QString &f_in, const QString &f_out, const std::function<QByteArray(QByteArray)> &func);

    static void moveOut(const QString &f_in, const QString &f_out, const std::function<QByteArray(QByteArray)> &func);

    void del(const PTabFile &file);

    void rename(const PTabFile &file);

    void initIfNeeded(MTab *tab, const QJsonObject &o);

    void readInfo(const QJsonObject &o) override;

    void writeInfo(QJsonObject &o) override;

    QWidget *getWidget();

};


#endif //ORGANIZER_SFILES_H
