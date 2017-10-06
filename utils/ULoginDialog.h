/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_ULOGINDIALOG_H
#define ORGANIZER_ULOGINDIALOG_H

#include <QtWidgets/QLabel>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <network/Network.h>


class ULoginDialog : public QDialog {
    QLabel *l_error;
    QLineEdit *l_log_login, *l_log_passw;
    QLineEdit *l_reg_login, *l_reg_passw, *l_reg_pass2;
    QCheckBox *c_log_rem, *c_reg_rem;

    QString login_hash;

    Network netw;

public:
    ULoginDialog();

    void tryLogin();

    void tryRegister();

    QHBoxLayout *newLabel(QString name, QString style);
};


#endif //ORGANIZER_ULOGINDIALOG_H
