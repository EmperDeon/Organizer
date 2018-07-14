/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <storage/SSecure.h>
#include <storage/Storage.h>
#include <utils/ULoginDialog.h>
#include <QtWidgets/QMessageBox>
#include "WSync.h"

QMenu *WSync::getMenu() {
    menu = new QMenu("Sync");
    auto *a_login = new QAction("Login", menu);
    QObject::connect(a_login, &QAction::triggered, this, &WSync::login);
    menu->addAction(a_login);

    auto *a_logout = new QAction("Logout", menu);
    QObject::connect(a_logout, &QAction::triggered, this, &WSync::logout);
    menu->addAction(a_logout);
    menu->addSeparator();

    auto *a_destroy = new QAction("Destroy your account", menu);
    QObject::connect(a_destroy, &QAction::triggered, this, &WSync::destroy);
    menu->addAction(a_destroy);

    updateMenu();

    return menu;
}

void WSync::updateMenu() {
    auto actions = menu->actions();
    auto st = Storage::getInstance();

    bool sync = st->getB("sync");

    actions[0]->setVisible(!sync);
    actions[1]->setVisible(sync);
}

void WSync::login() {
    ULoginDialog d;
    d.exec();

    updateMenu();
}

void WSync::logout() {
    if (QMessageBox::question(menu, QObject::tr("Logout"), QObject::tr("Are you sure, you want to logout ?")) ==
        QMessageBox::Yes) {
        auto st = Storage::getInstance();
        st->set("sync", false);

        if (QMessageBox::question(menu, QObject::tr("Logout"), QObject::tr("Keep docs ?")) == QMessageBox::No) {
            // TODO: Destroy docs and reload tabs
        }

        st->remove("login_hash");
        st->remove("login_date");
        st->remove("doc_key");
        st->remove("token");
    }

    updateMenu();
}

void WSync::destroy() {
    netw.request("auth/destroy");

    updateMenu();
}
