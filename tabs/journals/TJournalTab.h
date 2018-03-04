/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_TJOURNALTAB_H
#define ORGANIZER_TJOURNALTAB_H

#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <tabs/MTab.h>
#include <utils/widgets/UDatesWidget.h>


class TJournalTab : public MTab {
    int cur_mode;
    QHBoxLayout *m_layout;
    QButtonGroup *m_buttons;

    QJsonObject entries;
    QPlainTextEdit *edit;
    QTextEdit *view;
    UDatesWidget *dates;

public:
    explicit TJournalTab(const QJsonObject &o);

    QString getDesc() override;

    void importFrom(QString s) override {};

    QString exportTo() override { return ""; }

    void fromJson(QJsonValue v) override;

    QJsonValue toJson() override;

    void loadCustomParams(const QJsonObject &o) override;

    void saveCustomParams(QJsonObject &o) override;

    void updateText();

    void changeMode(int id, bool checked);

    void loadDate(const QString &name);

    void saveDate(const QString &id);

protected:
    // Slots
    void createdDate(UDateItem *item);

    void changedDate(const QString &old_id, UDateItem *item);

    void removedDate(const QString &name);

    void selectedDate(const QString &from, const QString &to);

    QStringList additionalInfo(const QString &id);
};

#endif //ORGANIZER_TJOURNALTAB_H
