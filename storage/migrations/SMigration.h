#ifndef ORGANIZER_SMIGRATION_H
#define ORGANIZER_SMIGRATION_H

#include <QtCore/QJsonObject>


class SMigration {
public:
    SMigration() = default;

    virtual int getVersion() = 0;

    virtual bool isNeededF(const QJsonObject &o) {
        return o["version"].toInt() < getVersion();
    }

    virtual bool isNeededD(const QJsonObject &o) {
        return o["version"].toInt() < getVersion();
    }

    // Full object
    virtual QJsonObject processF(QJsonObject o) = 0;

    // Documents
    virtual QJsonObject processD(QJsonObject o) = 0;
};


#endif //ORGANIZER_SMIGRATION_H
