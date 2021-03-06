/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <storage/SSettings.h>
#include <QtGui/QIntValidator>
#include "WSLineEdit.h"

WSLineEdit::WSLineEdit(const json_o &obj, Type t) : WSetting(obj), type(t) {
    widget = new QLineEdit;

    if (type == Integer) {
        widget->setText(QString::number(SSettings().getI(obj["name"])));
        widget->setValidator(new QIntValidator);

    } else {
        widget->setText(SSettings().getS(obj["name"]));
    }

    layout->addWidget(widget);
}

json WSLineEdit::value() {
    if (type == Integer) {
        return widget->text().toInt();

    } else {
        return widget->text();
    }
}
