/*
	Copyright (c) 2017 by Ilya Barykin
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
    menu->addAction("Login", this, &WSync::login);
    menu->addAction("Logout", this, &WSync::logout);
    menu->addSeparator();
    menu->addAction("Destroy your account", this, &WSync::destroy);

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
    if (QMessageBox::question(menu, tr("Logout"), tr("Are you sure, you want to logout ?")) == QMessageBox::Yes) {
        auto st = Storage::getInstance();
        st->set("sync", false);

        if (QMessageBox::question(menu, tr("Logout"), tr("Keep docs ?")) == QMessageBox::No) {
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
