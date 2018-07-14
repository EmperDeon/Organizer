/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_UPASSDIALOG_H
#define ORGANIZER_UPASSDIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QCheckBox>

class UPassDialog : public QDialog {
    QLineEdit *l_login, *l_passw;
    QCheckBox *c_rem;

public:
    UPassDialog();

    static QString getLoginHash(QString login);
};


#endif //ORGANIZER_UPASSDIALOG_H
