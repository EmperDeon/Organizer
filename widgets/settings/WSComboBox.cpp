/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <storage/SSettings.h>
#include "WSComboBox.h"

WSComboBox::WSComboBox(const json_o &obj) : WSetting(obj) {
    widget = new QComboBox;

    const QString &curr = SSettings().getS(s_name);

    int i = 0;
    for (const auto &entry : obj["list"]) {
        const QString val = entry[1];
        widget->addItem(entry[0].get<QString>(), val);

        if (curr == val)
            widget->setCurrentIndex(i);

        i++;
    }

    layout->addWidget(widget);
}

json WSComboBox::value() {
    return widget->currentData().toString();
}
