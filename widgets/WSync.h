/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

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
