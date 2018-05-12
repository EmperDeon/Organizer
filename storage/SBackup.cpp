/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtCore/QFile>
#include <QtCore/QJsonObject>
#include <vars.h>
#include <QtCore/QJsonDocument>
#include <crypt/CTools.h>
#include "SBackup.h"

void SBackup::addDocs(QString docs) {
    QString week = formattedWeek(), date = QDateTime::currentDateTime().toString(Qt::ISODate);

    QJsonObject week_backup, last_backup;
    QJsonObject backup = {
            {"docs", CTools::toBase(qCompress(docs.toUtf8(), 4))},
            {"date", QDate::currentDate().toString(Qt::ISODate)}
    };

    QFile f(BACKUP_FILE_WEEK);
    if (f.exists() && f.open(QFile::ReadOnly)) {
        week_backup = QJsonDocument::fromJson(f.readAll()).object();
        f.close();
    }

    if (!week_backup.contains(week)) {
        week_backup[week] = backup;
    }

    f.open(QFile::WriteOnly);
    f.write(QJsonDocument(week_backup).toJson());
    f.close();


    f.setFileName(BACKUP_FILE_LAST);
    if (f.exists() && f.open(QFile::ReadOnly)) {
        last_backup = QJsonDocument::fromJson(f.readAll()).object();
        f.close();
    }

    if (last_backup.keys().size() > 1) {
        QString k = last_backup.keys().takeFirst();
        last_backup.remove(k);
    }

    last_backup[date] = backup;

    f.open(QFile::WriteOnly);
    f.write(QJsonDocument(last_backup).toJson());
    f.close();
}

QString SBackup::formattedWeek(QDate date) {
    return QString("%1-%2").arg(date.year()).arg(date.weekNumber());
}
