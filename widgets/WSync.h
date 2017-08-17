#ifndef ORGANIZER_WSYNC_H
#define ORGANIZER_WSYNC_H

#include <QtCore/QObject>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <network/Network.h>


class WSync : public QObject {
    QMenu *menu = nullptr;

    Network netw;

public:
    WSync() = default;

    QMenu *getMenu();

    void updateMenu();

    void login();

    void logout();

    void destroy();
};


#endif //ORGANIZER_WSYNC_H
