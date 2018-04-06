/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_WSLEVEL_H
#define ORGANIZER_WSLEVEL_H

#include <QtWidgets/QWidget>
#include <QtCore/QJsonValue>


class WSetting : public QWidget {
protected:
    QWidget *widget;

public:
    explicit WSetting(const QJsonObject &obj);

    virtual QWidget *createWidget(const QJsonValue &value) = 0;

    virtual QJsonValue value() = 0;
};


#endif //ORGANIZER_WSLEVEL_H
