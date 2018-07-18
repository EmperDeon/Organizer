/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_SMVER02_H
#define ORGANIZER_SMVER02_H

#include "storage/migrations/SMigration.h"


class SMVer02 : public SMigration {
public:
    QString getVersion() override;

    QJsonObject processF(QJsonObject o) override;

    QJsonObject processD(QJsonObject o) override;
};


#endif //ORGANIZER_SMVER02_H
