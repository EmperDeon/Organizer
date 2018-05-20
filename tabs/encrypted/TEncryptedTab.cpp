/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <tabs/MTabsController.h>
#include <utils/logs/ULogger.h>
#include <utils/widgets/UCenteredWidget.h>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QInputDialog>
#include "TEncryptedTab.h"

TEncryptedTab::TEncryptedTab(const QJsonObject &o) : MTab(o, MTab::Encrypted) {
    layout = new QVBoxLayout;

    layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(createPassWidget());

    setLayout(layout);

    load();
}

QWidget *TEncryptedTab::createPassWidget() {
    auto *w = new UCenteredWidget(300, 150);
    auto *l = new QVBoxLayout;

    auto *l_title = new QLabel(tr("Enter password: "));

    l_title->setProperty("class", "h2");

    w_password = new QLineEdit;
    w_password->setEchoMode(QLineEdit::Password);

    auto *b_unlock = new QPushButton(tr("Unlock"));
    b_unlock->setProperty("class", "btn-lg");
    b_unlock->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

    connect(b_unlock, &QPushButton::clicked, this, &TEncryptedTab::tryUnlock);

    l->addWidget(l_title);
    l->addWidget(w_password);
    l->addWidget(b_unlock);

    w->setBoxLayout(l);
    return w;
}

void TEncryptedTab::lock() {
    layout->itemAt(0)->widget()->setVisible(true);

    // TODO: Add animations
    if (layout->count() > 1) {
        layout->itemAt(1)->widget()->setVisible(false);
    } else {
        logE("Lock called when Tab is NULL");
    }

    logD("Locked successfully");
    locked = true;
}

void TEncryptedTab::unlock() {
    locked = false;

    layout->itemAt(0)->widget()->setVisible(false);

    if (layout->count() == 1) {
        layout->addWidget(createTab());
        logD("Unlocked tab for first time");

    } else {
        layout->itemAt(1)->widget()->setVisible(true);
    }

    logD("Unlocked successfully");
}

void TEncryptedTab::tryUnlock() {
    if (password_hash == Utils::hash(w_password->text())) {
        password = w_password->text();
        unlock();

    } else {
        w_password->setStyleSheet("border-bottom: 1px solid red");
        logD("Wrong password");
    }
}

MTab *TEncryptedTab::createTab() {
    QJsonObject t_obj = obj;
    CAes aes(E_TAB_CIPHER, Utils::toBase(password.toLatin1()));
    QString decrypted_content = aes.decrypt(content);

    t_obj["content"] = Utils::serializeFromString(decrypted_content);

    tab = MTabsController::tabForType(t_obj, tab_type);
    return tab;
}

void TEncryptedTab::fromJson(QJsonValue v) {
    content = v.toString();

    if (!locked && tab != nullptr) {
        CAes aes(E_TAB_CIPHER, Utils::toBase(password.toLatin1()));
        QString decrypted_content = aes.decrypt(content);

        tab->fromJson(Utils::serializeFromString(decrypted_content));
    }
}

QJsonValue TEncryptedTab::toJson() {
    if (!locked && tab != nullptr) {
        CAes aes(E_TAB_CIPHER, Utils::toBase(password.toLatin1()));
        QString decrypted_content = Utils::serializeToString(tab->toJson());

        content = aes.encrypt(decrypted_content);
    }

    return content;
}

void TEncryptedTab::loadCustomParams(const QJsonObject &o) {
    // TODO: Store password in SSecure

    remember_me = o["remember_me"].toBool(false);
    password = o["password"].toString("");
    password_hash = o["password_hash"].toString("");
    tab_type = o["tab_type"].toInt();

    if (!locked && tab != nullptr) {
        tab->loadCustomParams(o);
    }
}

void TEncryptedTab::saveCustomParams(QJsonObject &o) {
    if (!locked && tab != nullptr) {
        tab->saveCustomParams(o);
    }

    // Don't forget to add to MTab::save if adding new

    o["password_hash"] = password_hash;
    o["remember_me"] = remember_me;

    if (remember_me)
        o["password"] = password;
}

void TEncryptedTab::toggleEncryption(MTab *tab) {
    if (tab->type == MTab::NewTab)
        return;

    if (tab->type != Encrypted) { // Encryption
        QString password = QInputDialog::getText(tab, tr("Enter password for encryption"), tr("Password"),
                                                 QLineEdit::Password);

        if (password.isEmpty())
            return;

        CAes aes(E_TAB_CIPHER, Utils::toBase(password.toLatin1()));
        tab->obj[S_REPLACE_KEY] = aes.encrypt(Utils::serializeToString(tab->toJson()));
        tab->obj["tab_type"] = tab->type;
        tab->obj["password_hash"] = Utils::hash(password);
        tab->type = Encrypted;

        auto *main = WMain::getInstance();
        main->contr->save();
        main->recreateTabs();

    } else { // Decryption
        auto *e_tab = dynamic_cast<TEncryptedTab *>(tab);

        if (e_tab->password.isEmpty()) {
            e_tab->password = QInputDialog::getText(tab, tr("Enter password for decryption"), tr("Password"),
                                                    QLineEdit::Password);
        }

        CAes aes(E_TAB_CIPHER, Utils::toBase(e_tab->password.toLatin1()));
        e_tab->obj[S_REPLACE_KEY] = Utils::serializeFromString(aes.decrypt(e_tab->toJson().toString()));
        e_tab->obj[S_DELETE_KEYS] = true;
        e_tab->type = MTab::tabType(e_tab->tab_type);

        auto *main = WMain::getInstance();
        main->contr->save();
        main->recreateTabs();
    }
}
