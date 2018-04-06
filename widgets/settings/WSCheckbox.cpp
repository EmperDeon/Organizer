/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QCheckBox>
#include "WSCheckbox.h"

QWidget *WSCheckbox::createWidget(const QJsonValue &value) {
    auto *w = new QCheckBox;

    w->setChecked(value.toBool());

    return w;
}

QJsonValue WSCheckbox::value() {
    return dynamic_cast<QCheckBox *>(widget)->isChecked();
}
