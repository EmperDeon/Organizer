/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QLabel>
#include <storage/SSettings.h>
#include "WSetting.h"

WSetting::WSetting(const json_o &obj) {
    layout = new QHBoxLayout;

    s_name = obj["name"].get<QString>();

    layout->addWidget(new QLabel(obj["description"].get<QString>()));

    setLayout(layout);
}
