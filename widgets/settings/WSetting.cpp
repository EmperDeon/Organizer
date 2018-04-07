/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QLabel>
#include <storage/SSettings.h>
#include "WSetting.h"

WSetting::WSetting(const QJsonObject &obj) {
    layout = new QHBoxLayout;

    s_name = obj["name"].toString();

    layout->addWidget(new QLabel(obj["description"].toString()));

    setLayout(layout);
}
