/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QVBoxLayout>
#include "TFileGroup.h"

TFileGroup::TFileGroup(const json_o &o) : Tab(o, Tab::FilesGroup) {
    auto *l = new QVBoxLayout;

    files = new PTabFiles;

    l->addWidget(files->getWidget());

    setLayout(l);

    load();
}

void TFileGroup::loadCustomParams(const json_o &o) {
    files->initIfNeeded(this, o);

    files->readInfo(o);
}

void TFileGroup::saveCustomParams(json_o &o) {
    files->writeInfo(o);
}
