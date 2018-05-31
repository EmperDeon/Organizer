/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QFormLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtCore/QTimer>
#include <vendor/simple_ossl/include/simple_ossl.h>
#include "ULoginDialog.h"

ULoginDialog::ULoginDialog() {
    auto *l = new QFormLayout;

    auto l_lay = new QHBoxLayout;
    l_error = new QLabel;
    l_error->setStyleSheet("color: red; font-size: 16px");
    l_error->setVisible(false);

    l_lay->addWidget(l_error);
    l_lay->setAlignment(Qt::AlignCenter);
    l->addRow(l_lay);

    l->addRow(newLabel(tr("Login"), "font-size: 24px"));

    l_log_login = new QLineEdit;
    l_log_passw = new QLineEdit;
    c_log_rem = new QCheckBox;
    auto *b_log = new QPushButton(tr("Login"));

    l->addRow("Login: ", l_log_login);
    l->addRow("Password: ", l_log_passw);
    l->addRow("Remember ?", c_log_rem);
    l->addRow(b_log);
    connect(b_log, &QPushButton::clicked, this, &ULoginDialog::tryLogin);


    l->addRow(newLabel(tr("Or"), "padding: 14px; font-size: 10px; color: #aaa"));

    l->addRow(newLabel(tr("Register"), "font-size: 24px"));


    l_reg_login = new QLineEdit;
    l_reg_passw = new QLineEdit;
    l_reg_pass2 = new QLineEdit;
    c_reg_rem = new QCheckBox;
    auto *b_reg = new QPushButton(tr("Register"));

    l->addRow("Login: ", l_reg_login);
    l->addRow("Password: ", l_reg_passw);
    l->addRow("Retype password: ", l_reg_pass2);
    l->addRow("Remember ?", c_reg_rem);
    l->addRow(b_reg);
    connect(b_reg, &QPushButton::clicked, this, &ULoginDialog::tryRegister);

    setLayout(l);
}

void ULoginDialog::tryLogin() {
    auto storage = Storage::getInstance();
    login_hash = Utils::hash(l_log_login->text() + ":" + l_log_passw->text());

    QJsonObject o = netw.request("auth/login", {
            {"login", login_hash}
    }).toObject();

    if (o["status"].toString() == "login_ok") {
        storage->set("doc_key", o["key"]);
        storage->set("token", o["token"]);
        storage->set("sync", true);

        storage->set("login_hash", login_hash);
        storage->set("login_date", QDateTime::currentMSecsSinceEpoch() / 1000);

        storage->saveJson();

        accept();
    } else {
        l_error->setText(o["message"].toString());
        l_error->setVisible(true);
    }
}

void ULoginDialog::tryRegister() {
    auto storage = Storage::getInstance();
    login_hash = Utils::hash(l_reg_login->text() + ":" + l_reg_passw->text());

    QString key = SimpleOSSL::generateAesKeyStr(S_DOC_KEY_SIZE);

    CAes aes("256", login_hash);
    storage->set("doc_key", aes.encrypt(key));

    QJsonObject o = netw.request("auth/register", {
            {"login", login_hash},
            {"key",   storage->getS("doc_key")}
    }).toObject();

    if (o["status"].toString() == "reg_ok") {
        storage->set("token", o["token"]);
        storage->set("sync", true);

        storage->set("login_hash", login_hash);
        storage->set("login_date", QDateTime::currentMSecsSinceEpoch() / 1000);

        storage->saveJson();
    } else {
        l_error->setText(o["message"].toString());
        l_error->setVisible(true);
    }
}

QHBoxLayout *ULoginDialog::newLabel(QString name, QString style) {
    auto l_lay = new QHBoxLayout;
    auto l_lab = new QLabel(name);
    l_lab->setStyleSheet(style);

    l_lay->addWidget(l_lab);
    l_lay->setAlignment(Qt::AlignCenter);

    return l_lay;
}
