/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_WSBASIC_H
#define ORGANIZER_WSBASIC_H

#include <QtWidgets/QWidget>
#include "WSetting.h"


class WSCheckbox : public WSetting {
public:
    explicit WSCheckbox(const QJsonObject &obj) : WSetting(obj) {}

    QWidget *createWidget(const QJsonValue &value) override;

    QJsonValue value() override;
};


#endif //ORGANIZER_WSBASIC_H
