/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_SMVER1_H
#define ORGANIZER_SMVER1_H

#include <storage/migrations/SMigration.h>

class SMVer1 : public SMigration {
public:
    int getVersion() override;

    QJsonObject processF(QJsonObject o) override;

    QJsonObject processD(QJsonObject o) override;
};


#endif //ORGANIZER_SMVER1_H
