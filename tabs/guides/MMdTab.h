#ifndef ORGANIZER_MMDTAB_H
#define ORGANIZER_MMDTAB_H


#include <QtCore/QJsonObject>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QButtonGroup>
#include "tabs/MTab.h"

class MMdTab : public MTab {
    int cur_mode;

    QPlainTextEdit *edit;
    QTextEdit *view;
    QScrollArea *view_scroll;

    QHBoxLayout *m_layout;
    QButtonGroup *m_buttons;


public:
    explicit MMdTab(const QJsonObject &o);

    QString getDesc() override;

    void importFrom(QString s) override;

    QString exportTo() override;

    void fromJson(QJsonValue v) override;

    QJsonValue toJson() override;

    void loadCustomParams(const QJsonObject &o) override;

    QJsonObject saveCustomParams() override;

    void updateText();

    void changeMode(int id, bool checked);
};


#endif //ORGANIZER_MMDTAB_H
