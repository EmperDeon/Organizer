/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtCore/QFile>
#include <vars.h>
#include <QtCore/QDebug>
#include <utils/Utils.h>
#include <QtCore/QTimer>
#include <QtWidgets/QApplication>
#include <QtCore/QSaveFile>
#include <vendor/verdigris/src/wobjectimpl.h>
#include "ULogger.h"

/*
 * Defines used in place of SSettings, because class can cause recursive calls
 * */

ULogger::ULogger() {
    mutex = new QMutex;

    auto *timer = new QTimer;

    connect(timer, &QTimer::timeout, this, &ULogger::save);
    connect(qApp, &QApplication::aboutToQuit, this, &ULogger::save);

    moveOldLogs();

    timer->start(1000);
}

void ULogger::log(ULogger::Level lev, const QDateTime &time, const QString &func, const QString &mess) {
    auto *logger = getInstance();
    QMutexLocker l(logger->mutex);

    const QString &entry = toLogEntry(lev, time, func, mess);
    logger->queue.enqueue(entry);

    l.unlock();

    if (lev == Error || lev == Warning)
        logger->save();

    emit logger->logEntryAdded(entry);

#ifdef DEBUG
    if (lev != Verbose)
        if (lev == Error || lev == Warning) {
            fprintf(stderr, "%s\n", entry.toStdString().c_str());
        } else {
            fprintf(stdout, "%s\n", entry.toStdString().c_str());
        }
#endif
}

void ULogger::save() {
    QByteArray bytes;
    bytes = logs().toUtf8();

    if (!changed)
        return;

    QSaveFile f(LOG_FILE);
    f.open(QFile::WriteOnly);

#if LOG_COMPRESSION > 0
    bytes = qCompress(bytes, LOG_COMPRESSION);
#endif

    f.write(bytes);
    f.commit();

    changed = false;
}

QString ULogger::toLogEntry(ULogger::Level level, const QDateTime &time, const QString &func, const QString &mess) {
    QRegExp regexp(R"(((\w+)::)?(\w+)\()");
    regexp.indexIn(func);

    QStringList func_components = regexp.capturedTexts();
    QString f_class = func_components[2],
            f_func = func_components[3],
            formatted = QString("[%1][%2][%3]: %4").arg(time.toString(LOG_DATE_FORMAT)).arg(levelToString(level));

#ifdef LOG_INCLUDE_METHOD
    if (!(f_class.isEmpty() || f_func.isEmpty())) {
        formatted = formatted.arg(f_class + "::" + f_func);
    } else if (f_class.isEmpty()) {
        formatted = formatted.arg(f_func);
    } else {
        formatted = formatted.arg("");
    }
#else
    formatted = formatted.arg(f_class);
#endif

    return formatted.arg(mess);
}

QString ULogger::levelToString(ULogger::Level level) {
    switch (level) {
        case Error:
            return "E";
        case Warning:
            return "W";
        case Info:
            return "I";
        case Debug:
            return "D";
        case Verbose:
            return "V";
        default:
            return "I";
    }
}

void ULogger::moveOldLogs() {
    // TODO: Rename files, and zip excess
}

QString ULogger::logs() {
    auto *inst = getInstance();
    QMutexLocker l(inst->mutex);

    while (!inst->queue.isEmpty()) {
        inst->output += inst->queue.dequeue() + '\n';

        inst->changed = true;
    }

    return inst->output;
}

ULogger::Level ULogger::levelFromString(const QString &level) {
    switch (level.at(0).toLatin1()) {
        case 'E':
            return Error;
        case 'W':
            return Warning;
        case 'I':
            return Info;
        case 'D':
            return Debug;
        case 'V':
            return Verbose;
        default:
            return Info;
    }
}

W_OBJECT_IMPL(ULogger)
