/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include "WFile.h"
#include "WFileIcon.h"

WFile::WFile(const PTabFile &f) : file(f) {
    auto *l = new QHBoxLayout;

    auto *l_icon = new WFileIcon(f.type);
    auto *l_name = new QLabel(f.name);
    auto *l_size = new QLabel(f.size);

    auto
            *b_del = createButton(":/icons/file-del.png", "Delete"),
            *b_edit = createButton(":/icons/file-edit.png", "Edit"),
            *b_save = createButton(":/icons/file-save.png", "Save");


    l_name->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    l_name->setStyleSheet("font-size: 14px;");

    l_size->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    l_size->setStyleSheet("font-size: 13px;");


    connect(b_save, &QPushButton::clicked, this, &WFile::int_save);
    connect(b_edit, &QPushButton::clicked, this, &WFile::int_edit);
    connect(b_del, &QPushButton::clicked, this, &WFile::int_del);


    l->addWidget(l_icon);
    l->addWidget(l_name);
    l->addSpacing(10);
    l->addWidget(l_size, 0, Qt::AlignLeft);
//    l->addSpacing(10);
    l->addWidget(b_save);
    l->addWidget(b_edit);
    l->addWidget(b_del);

    setLayout(l);
}

QPushButton *WFile::createButton(const QString &icon, const QString &tooltip) const {
    auto *r = new QPushButton(QIcon(icon), "");
    auto size = QSize(24, 24);
    r->setToolTip(tooltip);

    r->setFixedSize(size);
    r->setIconSize(size);
    r->setProperty("transparentBackground", true);

    return r;
}

void WFile::int_save() {
    emit save(file);
}

void WFile::int_edit() {
    emit edit(file);
}

void WFile::int_del() {
    emit del(file);
}
