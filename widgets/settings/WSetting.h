/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_WSLEVEL_H
#define ORGANIZER_WSLEVEL_H

#include <QtWidgets/QWidget>
#include <QtCore/QJsonValue>
#include <QtWidgets/QHBoxLayout>


class WSetting : public QWidget {
protected:
    QHBoxLayout *layout;
    QString s_name;

public:
    explicit WSetting(const QJsonObject &obj);

    QString name() { return s_name; }

    virtual QJsonValue value() = 0;
};


#endif //ORGANIZER_WSLEVEL_H
