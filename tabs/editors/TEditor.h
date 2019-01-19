/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_TEDITOR_H
#define ORGANIZER_TEDITOR_H

#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <tabs/Tab.h>


class TEditor : public Tab {
    int cur_mode = 0;

    QPlainTextEdit *edit;
    QTextEdit *view;

    QHBoxLayout *m_layout;
    QButtonGroup *m_buttons;

public:
    explicit TEditor(const json_o &o);

    void fromJson(json v) override;

    json toJson() override;

    void loadCustomParams(const json_o &o) override;

    void saveCustomParams(json_o &o) override;

    void updateText();

    void changeMode(int id, bool checked);
};

#endif //ORGANIZER_TEDITOR_H
