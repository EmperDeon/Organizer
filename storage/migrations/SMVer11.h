/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_SMVER11_H
#define ORGANIZER_SMVER11_H

#include "storage/migrations/SMigration.h"


class SMVer11 : public SMigration {
public:
    QString getVersion() override;

    QJsonObject processF(QJsonObject o) override;

    QJsonObject processD(QJsonObject o) override;
};


#endif //ORGANIZER_SMVER11_H
