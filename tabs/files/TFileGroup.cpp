/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QVBoxLayout>
#include "TFileGroup.h"

TFileGroup::TFileGroup(const QJsonObject &o) : Tab(o, Tab::FilesGroup) {
    auto *l = new QVBoxLayout;

    files = new PTabFiles;

    l->addWidget(files->getWidget());

    setLayout(l);

    load();
}

void TFileGroup::loadCustomParams(const QJsonObject &o) {
    files->initIfNeeded(this, o);

    files->readInfo(o);
}

void TFileGroup::saveCustomParams(QJsonObject &o) {
    files->writeInfo(o);
}
