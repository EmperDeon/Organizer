/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QVBoxLayout>
#include <storage/Storage.h>
#include "WFile.h"
#include <QtWidgets/QFileDialog>
#include <QtCore/QTimer>

WFiles::WFiles(PTabFiles *s_f) : files(s_f) {
    auto *l = new QVBoxLayout;

    list_l = new QVBoxLayout;
    scroll = new UScrollArea(list_l);
    auto *b_add = new QPushButton(tr("Add new file"));

    list_l->setAlignment(Qt::AlignTop);
    b_add->setProperty("newLineButton", "true");

    connect(b_add, &QPushButton::clicked, this, &WFiles::addFile);

    l->addWidget(scroll);
    l->addWidget(b_add);

    updateFileList();

    setLayout(l);
}

void WFiles::updateFileList() {
    static QList<WFile *> file_widgets = {};

    for (auto *f : file_widgets) {
        f->deleteLater();
    }
    file_widgets.clear();

    for (const auto &f : files->getFiles()) {
        auto *t = new WFile(f);

        connect(t, &WFile::save, this, &WFiles::saveFile);
        connect(t, &WFile::edit, this, &WFiles::editFile);
        connect(t, &WFile::del, this, &WFiles::delFile);

        file_widgets << t;
        list_l->addWidget(t);
    }
}

void WFiles::addFile() {
    files->addFile(QFileDialog::getOpenFileName(this, tr("Choose file to be added")));

    updateFileList();
}

void WFiles::delFile(const PTabFile &f) {
    files->del(f);

    QTimer::singleShot(10, [=]() {
        updateFileList();
    });
}

void WFiles::saveFile(const PTabFile &f) {
    files->saveFile(QFileDialog::getExistingDirectory(this, tr("Choose folder to save file")), f);
}

void WFiles::editFile(const PTabFile &f) {
    files->rename(f);

    updateFileList();
}
