#ifndef ORGANIZER_PTABPLUGIN_H
#define ORGANIZER_PTABPLUGIN_H

#include <plugins/Plugin.h>
#include <QtCore/QJsonObject>


class PTabPlugin : public Plugin {
public:
    virtual void readInfo(const QJsonObject &o) = 0;

    virtual void writeInfo(QJsonObject &o) = 0;
};


#endif //ORGANIZER_PTABPLUGIN_H
