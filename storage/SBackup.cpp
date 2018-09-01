/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtCore/QFile>
#include <vendor/additions.h>
#include <vars.h>
#include <QtCore/QJsonDocument>
#include <utils/Utils.h>
#include "SBackup.h"

void SBackup::addDocs(QString docs) {
    QString week = formattedWeek(), date = QDateTime::currentDateTime().toString(Qt::ISODate);

    json_o week_backup, last_backup;
    json_o backup = {
            {"docs", Utils::toBase(qCompress(docs.toUtf8(), 4))},
            {"date", QDate::currentDate().toString(Qt::ISODate)}
    };

    QFile f(BACKUP_FILE_WEEK);
    if (f.exists() && f.open(QFile::ReadOnly)) {
        week_backup = json::parse(QString::fromUtf8(f.readAll()).toStdString());
        f.close();
    }

    if (!week_backup.contains(week)) {
        week_backup[week] = backup;
    }

    f.open(QFile::WriteOnly);
    f.write(week_backup.dumpQ().toUtf8());
    f.close();


    f.setFileName(BACKUP_FILE_LAST);
    if (f.exists() && f.open(QFile::ReadOnly)) {
        last_backup = json::parse(QString::fromUtf8(f.readAll()).toStdString());
        f.close();
    }

    if (last_backup.keys().size() > 1) {
        QString k = last_backup.keys().takeFirst();
        last_backup.erase(k);
    }

    last_backup[date] = backup;

    f.open(QFile::WriteOnly);
    f.write(last_backup.dumpQ().toUtf8());
    f.close();
}

QString SBackup::formattedWeek(QDate date) {
    return QString("%1-%2").arg(date.year()).arg(date.weekNumber());
}
