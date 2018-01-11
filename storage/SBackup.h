/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_SBACKUP_H
#define ORGANIZER_SBACKUP_H


#include <QtCore/QString>
#include <QtCore/QDate>

class SBackup {

public:
    static void addDocs(QString docs);

    static QString formattedWeek(QDate date = QDate::currentDate());
};


#endif //ORGANIZER_SBACKUP_H
