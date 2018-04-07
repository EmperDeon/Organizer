/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QCheckBox>
#include "WSCheckBox.h"
#include <storage/SSettings.h>

WSCheckBox::WSCheckBox(const QJsonObject &obj) : WSetting(obj) {
    widget = new QCheckBox;

    widget->setChecked(SSettings::getB(obj["name"].toString()));

    layout->addWidget(widget);
}

QJsonValue WSCheckBox::value() {
    return widget->isChecked();
}
