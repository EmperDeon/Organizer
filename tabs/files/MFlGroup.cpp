#include <QtWidgets/QVBoxLayout>
#include "MFlGroup.h"

MFlGroup::MFlGroup(const QJsonObject &o) : MTab(o, MTab::FilesGroup) {
    auto *l = new QVBoxLayout;

    files = new PTabFiles;

    l->addWidget(files->getWidget());

    setLayout(l);

    load();
}

QString MFlGroup::getDesc() {
    return "Files: " + name;
}

void MFlGroup::loadCustomParams(const QJsonObject &o) {
    files->initIfNeeded(this, o);

    files->readInfo(o);
}

void MFlGroup::saveCustomParams(QJsonObject &o) {
    files->writeInfo(o);
}
