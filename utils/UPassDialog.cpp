/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <utils/Utils.h>
#include <storage/Storage.h>
#include <QtCore/QTimer>
#include "UPassDialog.h"

UPassDialog::UPassDialog() {
    auto *l = new QFormLayout;

    l_login = new QLineEdit;
    l_passw = new QLineEdit;
    c_rem = new QCheckBox;

    l->addRow("Login: ", l_login);
    l->addRow("Password: ", l_passw);
    l->addRow("Remember ?", c_rem);

    QPushButton *b_acc = new QPushButton("OK"), *b_rej = new QPushButton("Cancel");

    l->addRow(b_acc, b_rej);

    connect(b_acc, &QPushButton::clicked, this, &UPassDialog::accept);
    connect(b_rej, &QPushButton::clicked, this, &UPassDialog::reject);

    setLayout(l);
}

QString UPassDialog::getLoginHash(QString login) {
    UPassDialog r;
    r.l_login->setText(login);

    if (r.exec() != 0) {
        QString str = r.l_login->text() + ":" + r.l_passw->text();
        QString last_login = r.l_login->text();
        bool rem = r.c_rem->isChecked();

        QTimer::singleShot(10, [last_login, rem]() {
            Storage::getInstance()->set("last_login", last_login);
            Storage::getInstance()->set("remember", rem);

        });

        return Utils::hash(str);

    }

    return "";

}
