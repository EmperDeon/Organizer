/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <tabs/TabsController.h>
#include <utils/logs/ULogger.h>
#include <utils/widgets/UCenteredWidget.h>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFormLayout>
#include <QtCore/QtCore>
#include "TEncryptedTab.h"

TEncryptedTab::TEncryptedTab(const json_o &o) : Tab(o, Tab::Encrypted) {
    layout = new QVBoxLayout;

    layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);

    setLayout(layout);

    load();
}

QWidget *TEncryptedTab::createPassWidget() {
    auto *w = new UCenteredWidget(300, 200);
    auto *l = new QVBoxLayout;

    auto *l_title = new QLabel(tr("Enter password: "));

    l_title->setProperty("class", "h2");

    w_password = new QLineEdit;
    w_password->setEchoMode(QLineEdit::Password);

    w_remember = createRememberWidget();
    w_remember_check = new QCheckBox(tr("Remember password ?"));

    auto *hl = new QHBoxLayout;
    auto *b_unlock = new QPushButton(tr("Unlock"));
    w_forget = new QPushButton(tr("Forget me"));

    b_unlock->setProperty("class", "btn-lg");
    b_unlock->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

    w_forget->setProperty("class", "btn-lg");
    w_forget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

    hl->addWidget(b_unlock);
    hl->addWidget(w_forget);

    connect(w_password, &QLineEdit::returnPressed, this, &TEncryptedTab::tryUnlock);
    connect(b_unlock, &QPushButton::clicked, this, &TEncryptedTab::tryUnlock);
    connect(w_forget, &QPushButton::clicked, [&]() {
        remember_me = false;
        updateState();
    });
    connect(w_remember_check, &QCheckBox::stateChanged, [=](int s) {
        w_remember->setVisible(s == 2);
    });

    l->addWidget(l_title);
    l->addWidget(w_password);
    l->addWidget(w_remember_check);
    l->addWidget(w_remember);
    l->addLayout(hl);

    w->setBoxLayout(l);
    return w;
}

QWidget *TEncryptedTab::createRememberWidget() {
    auto *w = new QWidget;
    auto *l = new QFormLayout;

    w_remember_period = new QComboBox;

    l->addRow(tr("Period"), w_remember_period);

    addRememberPeriods();

    w->setLayout(l);
    w->setVisible(false);

    return w;
}

void TEncryptedTab::lock() {
    if (locked) {
        return;
    }

    layout->itemAt(0)->widget()->setVisible(true);
    updateState();

    // TODO: Add animations
    if (layout->count() > 1) {
        layout->itemAt(1)->widget()->setVisible(false);
    } else {
        logE("Lock called when Tab is NULL");
    }

    updateState();
    logD("Locked successfully");
    locked = true;
}

void TEncryptedTab::unlock() {
    if (!locked) {
        return;
    }

    locked = false;

    layout->itemAt(0)->widget()->setVisible(false);

    if (layout->count() == 1) {
        layout->addWidget(createTab());
        logD("Unlocked tab for first time");

    } else {
        layout->itemAt(1)->widget()->setVisible(true);
    }

    w_password->clear();
    fromJson(content);
    logD("Unlocked successfully");
}

void TEncryptedTab::tryUnlock() {
    if (remember_me) {
        if (remember_until > QDateTime::currentSecsSinceEpoch()) {
            return unlock();
        } else {
            remember_me = false;
            updateState();
        }
    }

    if (password_hash == Crypt::hash(w_password->text())) {
        password = w_password->text();

        if (w_remember_check->isChecked()) { // If password is correct and remember checked
            remember_me = true;
            QDateTime time = QDateTime::currentDateTime();
            time = time.addSecs(w_remember_period->currentData(Qt::UserRole).toLongLong() * 60);
            remember_until = time.toSecsSinceEpoch();
        }

        unlock();
        w_password->setStyleSheet("border-bottom: none");

    } else {
        w_password->setStyleSheet("border-bottom: 1px solid red");
        logD("Wrong password");
    }
}

Tab *TEncryptedTab::createTab() {
    json_o t_obj = obj;
    CAes aes(E_TAB_CIPHER, Crypt::deriveKey(password));
    QString decrypted_content = aes.decrypt(content);

    t_obj["content"] = json::parse(decrypted_content.toStdString());

    tab = TList::createNew(t_obj, tab_type);
    return tab;
}

void TEncryptedTab::fromJson(json v) {
    content = v.get<QString>();

    if (!locked && tab != nullptr) {
        CAes aes(E_TAB_CIPHER, Crypt::deriveKey(password));
        QString decrypted_content = aes.decrypt(content);

        tab->fromJson(json::parse(decrypted_content.toStdString()));
    }
}

json TEncryptedTab::toJson() {
    if (!locked && tab != nullptr) {
        CAes aes(E_TAB_CIPHER, Crypt::deriveKey(password));
        QString decrypted_content = tab->toJson().dumpQ();

        content = aes.encrypt(decrypted_content);
    }

    return content;
}

void TEncryptedTab::loadCustomParams(const json_o &o) {
    remember_me = o["remember_me"];
    password_hash = o["password_hash"].get<QString>();
    tab_type = o["tab_type"];

    layout->insertWidget(0, createPassWidget());
    updateState();

    if (remember_me) {
        // TODO: Store passwords in SSecure
        password = o["remember_token"].get<QString>();
        remember_until = (qint64) (double) o["remember_until"];

        if (layout->count() < 2) {
            QTimer::singleShot(10, [&]() {
                tryUnlock();
            });
        }
    }

    if (!locked && tab != nullptr) {
        tab->loadCustomParams(o);
    }
}

void TEncryptedTab::saveCustomParams(json_o &o) {
    if (!locked && tab != nullptr) {
        tab->saveCustomParams(o);
    }

    // Don't forget to add to Tab::save if adding new

    o["password_hash"] = password_hash;
    o["remember_me"] = remember_me;

    if (remember_me) {
        o["remember_token"] = password;
        o["remember_until"] = remember_until;
    } else {
        o["remember_token"] = "";
        o["remember_until"] = "";
    }
}

void TEncryptedTab::toggleEncryption(Tab *tab) {
    if (tab->type == Tab::NewTab)
        return;

    if (tab->type != Encrypted) { // Encryption
        QString password = QInputDialog::getText(tab, tr("Enter password for encryption"), tr("Password"),
                                                 QLineEdit::Password);

        if (password.isEmpty())
            return;

        CAes aes(E_TAB_CIPHER, Crypt::deriveKey(password));
        tab->obj[S_REPLACE_KEY] = aes.encrypt(tab->toJson().dumpQ());
        tab->obj["tab_type"] = tab->type;
        tab->obj["password_hash"] = Crypt::hash(password);
        tab->type = Encrypted;

    } else { // Decryption
        auto *e_tab = dynamic_cast<TEncryptedTab *>(tab);

        if (e_tab->password.isEmpty()) {
            e_tab->password = QInputDialog::getText(tab, tr("Enter password for decryption"), tr("Password"),
                                                    QLineEdit::Password);
        }

        if (e_tab->password_hash != Crypt::hash(e_tab->password)) {
            if (QMessageBox::question(tab, tr("Decryption"), tr("Passwords do not match.\nErase all the data ?")) ==
                QMessageBox::No) {
                e_tab->password = "";
                return;
            }
        }

        CAes aes(E_TAB_CIPHER, Crypt::deriveKey(e_tab->password));
        e_tab->obj[S_REPLACE_KEY] = json::parse(aes.decrypt(e_tab->toJson()).toStdString());
        e_tab->obj[S_DELETE_KEYS] = true;
        e_tab->type = Tab::tabType(e_tab->tab_type);
    }

    auto *main = WMain::getInstance();
    main->contr->save();
    main->recreateTabs();
}

void TEncryptedTab::addRememberPeriods() {
    QStringList times = SSettings().getS("remember_periods").split(',');

    for (const QString &s_time : times) {
        qint64 t_time, time = s_time.toLongLong();

        QStringList out;

        if (time >= 1440) { // Days
            t_time = time / 1440;
            out += QString::number(t_time) + (t_time > 1 ? " days" : " day");
            time -= t_time * 1440;
        }

        if (time >= 60) { // Hours
            t_time = time / 60;
            out += QString::number(t_time) + (t_time > 1 ? " hours" : " hour");
            time -= t_time * 60;
        }

        if (time > 0) { // Minutes
            out += QString::number(time) + (time > 1 ? " minutes" : " minute");
        }

        w_remember_period->addItem(out.join(' '), s_time.toLongLong());
    }
}

void TEncryptedTab::updateState() {
    w_password->setEnabled(!remember_me);
    w_forget->setVisible(remember_me);
}

void TEncryptedTab::onSelected() {
    if (locked) {
        w_password->setFocus(Qt::TabFocusReason);
    }
}
