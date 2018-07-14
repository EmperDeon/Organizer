/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_SSECURE_H
#define ORGANIZER_SSECURE_H


#include <QtCore/QJsonObject>

class SSecure {
    QJsonObject *obj;

public:
    explicit SSecure(QJsonObject *o);

    QString password();

    void initNetworkInfo();
};


#endif //ORGANIZER_SSECURE_H
