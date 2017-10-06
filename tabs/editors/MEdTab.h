/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_MEDTAB_H
#define ORGANIZER_MEDTAB_H

#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <tabs/MTab.h>


class MEdTab : public MTab {
    int cur_mode;

    QPlainTextEdit *edit;
    QTextEdit *view;

    QHBoxLayout *m_layout;
    QButtonGroup *m_buttons;

public:
    explicit MEdTab(const QJsonObject &o);

    QString getDesc() override;

    void importFrom(QString s) override;

    QString exportTo() override;

    void fromJson(QJsonValue v) override;

    QJsonValue toJson() override;

    void loadCustomParams(const QJsonObject &o) override;

    void saveCustomParams(QJsonObject &o) override;

    void updateText();

    void changeMode(int id, bool checked);
};

#endif //ORGANIZER_MEDTAB_H
