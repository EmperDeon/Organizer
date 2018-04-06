/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <storage/SSettings.h>
#include "WSetting.h"

WSetting::WSetting(const QJsonObject &obj) {
    auto *l = new QHBoxLayout;

    l->addWidget(new QLabel(obj["description"].toString()));

    widget = createWidget(SSettings::get(obj["name"].toString()));
    l->addWidget(widget);

    setLayout(l);
}
