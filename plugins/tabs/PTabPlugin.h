/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_PTABPLUGIN_H
#define ORGANIZER_PTABPLUGIN_H

#include <plugins/Plugin.h>
#include <QtCore/QJsonObject>


class PTabPlugin : public Plugin {
public:
    virtual void readInfo(const QJsonObject &o) = 0;

    virtual void writeInfo(QJsonObject &o) = 0;
};


#endif //ORGANIZER_PTABPLUGIN_H
