/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_WSETTINGS_H
#define ORGANIZER_WSETTINGS_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QButtonGroup>
#include "WSetting.h"


class WSettings : public QWidget {
    QList<WSetting *> entries;
    QVBoxLayout *scroll;

public:
    WSettings();

    WSetting *createWidgetForType(const QJsonObject &obj);

    void save();
};


#endif //ORGANIZER_WSETTINGS_H
