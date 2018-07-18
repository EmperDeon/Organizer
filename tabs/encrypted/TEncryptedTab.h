/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_TENCRYPTEDTAB_H
#define ORGANIZER_TENCRYPTEDTAB_H

#include <vars.h>
#include <tabs/Tab.h>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>


class TEncryptedTab : public Tab {
    Tab *tab = nullptr;

    bool locked = true;
    QString content = "";

    QString password, password_hash;
    bool remember_me = false;
    qint64 remember_until;
    int tab_type;

    QVBoxLayout *layout;
    QLineEdit *w_password;
    QWidget *w_remember;
    QCheckBox *w_remember_check;
    QComboBox *w_remember_period;
    QPushButton *w_forget;


public:
    explicit TEncryptedTab(const QJsonObject &o);

    QWidget *createPassWidget();

    QWidget *createRememberWidget();

    Tab *createTab();

    void updateState();

    void lock();

    void unlock();

    void tryUnlock();

    void fromJson(QJsonValue v) override;

    QJsonValue toJson() override;

    void loadCustomParams(const QJsonObject &o) override;

    void saveCustomParams(QJsonObject &o) override;

    void onSelected() override;


    static void toggleEncryption(Tab *tab);

    void addRememberPeriods();
};


#endif //ORGANIZER_TENCRYPTEDTAB_H
