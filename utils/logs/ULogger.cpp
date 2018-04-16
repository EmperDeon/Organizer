/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtCore/QFile>
#include <vars.h>
#include <QtCore/QDebug>
#include <crypt/CTools.h>
#include <QtCore/QTimer>
#include <QtWidgets/QApplication>
#include "ULogger.h"

/*
 * Defines used in place of SSettings, because class can cause recursive calls
 * */

ULogger::ULogger() {
    mutex = new QMutex;

    auto *timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &ULogger::save);
    timer->start(1000);

    connect(qApp, &QApplication::aboutToQuit, this, &ULogger::save);
}

void ULogger::log(ULogger::Level lev, const QDateTime &time, const QString &func, const QString &mess) {
    auto *logger = getInstance();
    QMutexLocker l(logger->mutex);

    const QString &entry = toLogEntry(lev, time, func, mess);
    logger->queue.enqueue(entry);

    if (lev == Error || lev == Warning)
        logger->save();

#ifdef DEBUG
    if (lev != Verbose)
        puts(entry.toStdString().c_str());
#endif
}

void ULogger::save() {
    QMutexLocker l(mutex);
    QByteArray bytes;

    if (queue.isEmpty())
        return;

    while (!queue.isEmpty()) {
        logs += queue.dequeue() + '\n';
    }

    QFile f(LOG_FILE);
    f.open(QFile::WriteOnly);
    bytes = logs.toUtf8();

#if LOG_COMPRESSION > 0
    bytes = qCompress(bytes, LOG_COMPRESSION);
#endif

    f.write(bytes);
    f.close();
}

QString ULogger::toLogEntry(ULogger::Level level, const QDateTime &time, const QString &func, const QString &mess) {
    QRegExp regexp(R"(((\w+)::)?(\w+)\()");
    regexp.indexIn(func);

    QStringList func_components = regexp.capturedTexts();
    QString f_class = func_components[2],
            f_func = func_components[3],
            formatted = QString("[%1][%2][%3]: %4").arg(time.toString("dd.MM.yyyy HH:mm:ss")).arg(levelToString(level));

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

const QString ULogger::levelToString(ULogger::Level level) {
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
    }
}
