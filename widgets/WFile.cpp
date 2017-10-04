#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include "WFile.h"
#include "WFileIcon.h"

WFile::WFile(const SFile &f) {
    auto *l = new QHBoxLayout;

    auto *l_icon = new WFileIcon(f.type);
    auto *l_name = new QLabel(f.name);

    auto
            *b_del = createButton(":/icons/file-del.png", "Delete"),
            *b_edit = createButton(":/icons/file-edit.png", "Edit"),
            *b_save = createButton(":/icons/file-save.png", "Save");


    l_name->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    l_name->setStyleSheet("font-size: 16px;");

    l->addWidget(l_icon);

    l->addWidget(l_name);

    l->addSpacing(20);

    l->addWidget(b_save, 0, Qt::AlignRight);
    l->addWidget(b_edit, 0, Qt::AlignRight);
    l->addWidget(b_del, 0, Qt::AlignRight);

    setLayout(l);
}

QPushButton *WFile::createButton(const QString &icon, const QString &tooltip) const {
    auto *r = new QPushButton(QIcon(icon), "");

    r->setToolTip(tooltip);

    r->setIconSize(QSize(28, 28));
    r->setProperty("transparentBackground", true);
    r->setFixedSize(28, 28);

    return r;
}
