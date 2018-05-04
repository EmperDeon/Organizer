/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_ULOGGER_H
#define ORGANIZER_ULOGGER_H

#include <utils/USingleton.h>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QMutex>
#include <QtCore/QDateTime>
#include <QtCore/QQueue>

#define logE(m) ULogger::log(ULogger::Error, QDateTime::currentDateTime(), Q_FUNC_INFO, m)
#define logW(m) ULogger::log(ULogger::Warning, QDateTime::currentDateTime(), Q_FUNC_INFO, m)
#define logI(m) ULogger::log(ULogger::Info, QDateTime::currentDateTime(), Q_FUNC_INFO, m)
#define logD(m) ULogger::log(ULogger::Debug, QDateTime::currentDateTime(), Q_FUNC_INFO, m)
#define logV(m) ULogger::log(ULogger::Verbose, QDateTime::currentDateTime(), Q_FUNC_INFO, m)

#define ULOG_LEVEL_LIST QList<ULogger::Level> level_list = { ULogger::Error, ULogger::Warning, ULogger::Info, ULogger::Debug, ULogger::Verbose };


class ULogger : public QObject, public USingleton<ULogger> {
Q_OBJECT

public:
    enum Level {
        Error, Warning, Info, Debug, Verbose
    };

protected:
    QMutex *mutex;
    QQueue<QString> queue;

    // FIXME: Possibly could break, if more than 4 billion chars is written to log. Check
    // TODO:
    QString output;

    bool changed = false;

Q_SIGNALS:

    void logEntryAdded(const QString &log);

public:
    ULogger();

    static void log(ULogger::Level lev, const QDateTime &time, const QString &func, const QString &mess);

    static QString toLogEntry(ULogger::Level level, const QDateTime &time, const QString &func, const QString &mess);

    static const QString levelToString(ULogger::Level level);

    static const Level levelFromString(const QString &level);

    static const QString logs();

    void save();

    void moveOldLogs();
};

#endif //ORGANIZER_ULOGGER_H
