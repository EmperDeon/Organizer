/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_SMIGRATION_H
#define ORGANIZER_SMIGRATION_H

#include <QtCore/QJsonObject>


class SMigration {
public:
    SMigration() = default;

    virtual QString getVersion() = 0;

    virtual bool isNeeded(const QJsonObject &o) {
        return o["version"].toString() < getVersion();
    }

    // Full object
    virtual QJsonObject processF(QJsonObject o) = 0;

    // Documents
    virtual QJsonObject processD(QJsonObject o) = 0;
};


#endif //ORGANIZER_SMIGRATION_H
