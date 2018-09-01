/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_SFILES_H
#define ORGANIZER_SFILES_H

#include <crypt/CAes.h>
#include <functional>
#include <plugins/tabs/PTabPlugin.h>
#include <widgets/files/WFiles.h>
#include <tabs/Tab.h>
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

    int findFileByName(const QString &n);

    void del(const PTabFile &file);

    void rename(const PTabFile &file);

    void initIfNeeded(Tab *tab, const json_o &o);

    void readInfo(const json_o &o) override;

    void writeInfo(json_o &o) override;

    QWidget *getWidget();

};


#endif //ORGANIZER_SFILES_H
