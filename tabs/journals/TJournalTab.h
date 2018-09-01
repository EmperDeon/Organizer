/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_TJOURNALTAB_H
#define ORGANIZER_TJOURNALTAB_H

#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <tabs/Tab.h>
#include <utils/widgets/UDatesWidget.h>


class TJournalTab : public Tab {
    int cur_mode;
    QHBoxLayout *m_layout;
    QButtonGroup *m_buttons;

    json_o entries;
    QPlainTextEdit *edit;
    QTextEdit *view;
    UDatesWidget *dates;

public:
    explicit TJournalTab(const json_o &o);

    void fromJson(json v) override;

    json toJson() override;

    void loadCustomParams(const json_o &o) override;

    void saveCustomParams(json_o &o) override;

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
