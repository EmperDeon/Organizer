/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_WSLINEEDIT_H
#define ORGANIZER_WSLINEEDIT_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>
#include "WSetting.h"


class WSLineEdit : public WSetting {
public:
    enum Type {
        Normal, Integer
    };

private:
    QLineEdit *widget;
    Type type;

public:
    explicit WSLineEdit(const QJsonObject &obj, Type t = Normal);

    QJsonValue value() override;
};


#endif //ORGANIZER_WSLINEEDIT_H
