#ifndef ORGANIZER_MFLGROUP_H
#define ORGANIZER_MFLGROUP_H

#include <tabs/MTab.h>
#include <plugins/tabs/PTabFiles.h>


class MFlGroup : public MTab {
    PTabFiles *files;

public:
    explicit MFlGroup(const QJsonObject &o);

    QString getDesc() override;

    void loadCustomParams(const QJsonObject &o) override;

    void saveCustomParams(QJsonObject &o) override;
};


#endif //ORGANIZER_MFLGROUP_H
