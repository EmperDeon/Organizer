/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_WSCOMBOBOX_H
#define ORGANIZER_WSCOMBOBOX_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include "WSetting.h"


class WSComboBox : public WSetting {
private:
    QComboBox *widget;

public:
    explicit WSComboBox(const QJsonObject &obj);

    QJsonValue value() override;
};


#endif //ORGANIZER_WSCOMBOBOX_H
