/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_TENCRYPTEDTAB_H
#define ORGANIZER_TENCRYPTEDTAB_H

#include <vars.h>
#include <tabs/MTab.h>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>


class TEncryptedTab : public MTab {
    MTab *tab = nullptr;

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

    MTab *createTab();

    void updateState();

    void lock();

    void unlock();

    void tryUnlock();

    void fromJson(QJsonValue v) override;

    QJsonValue toJson() override;

    void loadCustomParams(const QJsonObject &o) override;

    void saveCustomParams(QJsonObject &o) override;


    static void toggleEncryption(MTab *tab);

    void addRememberPeriods();
};


#endif //ORGANIZER_TENCRYPTEDTAB_H
