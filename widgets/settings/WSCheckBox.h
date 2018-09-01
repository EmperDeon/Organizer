/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_WSBASIC_H
#define ORGANIZER_WSBASIC_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QCheckBox>
#include "WSetting.h"


class WSCheckBox : public WSetting {
    QCheckBox *widget;

public:
    explicit WSCheckBox(const json_o &obj);

    json value() override;
};


#endif //ORGANIZER_WSBASIC_H
