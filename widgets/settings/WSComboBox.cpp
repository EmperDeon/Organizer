/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <storage/SSettings.h>
#include "WSComboBox.h"

WSComboBox::WSComboBox(const QJsonObject &obj) : WSetting(obj) {
    widget = new QComboBox;

    const QString &curr = SSettings::getS(s_name);

    int i = 0;
    for (const auto &entry : obj["list"].toArray()) {
        const auto val = entry.toArray()[1].toString();
        widget->addItem(entry.toArray()[0].toString(), val);

        if (curr == val)
            widget->setCurrentIndex(i);

        i++;
    }

    layout->addWidget(widget);
}

QJsonValue WSComboBox::value() {
    return widget->currentData().toString();
}
