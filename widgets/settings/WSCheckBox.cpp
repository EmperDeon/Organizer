/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QCheckBox>
#include "WSCheckBox.h"
#include <storage/SSettings.h>

WSCheckBox::WSCheckBox(const json_o &obj) : WSetting(obj) {
    widget = new QCheckBox;

    widget->setChecked(SSettings().getB(obj["name"]));

    layout->addWidget(widget);
}

json WSCheckBox::value() {
    return widget->isChecked();
}
