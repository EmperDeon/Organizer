#include <QtWidgets/QVBoxLayout>
#include <storage/Storage.h>
#include "WFiles.h"
#include "WFile.h"

WFiles::WFiles(const QString &name) : WFiles(Storage::getFiles(name)) {}

WFiles::WFiles(SFiles *s_f) : files(s_f) {
    auto *l = new QVBoxLayout;

    list_l = new QVBoxLayout;
    scroll = new UScrollArea(list_l);

    l->addWidget(scroll);

    updateFileList();

    setLayout(l);
}

void WFiles::updateFileList() {
    static QList<WFile *> file_widgets = {};

    for (auto *f : file_widgets) {
        f->deleteLater();
    }

    for (const auto &f : files->getFiles()) {
        auto *t = new WFile(f);

        file_widgets << t;
        list_l->addWidget(t);
    }
}
