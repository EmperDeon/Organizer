/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_UDATEWIDGET_H
#define ORGANIZER_UDATEWIDGET_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTimeEdit>


class UDateDialog : public QDialog {
    QCalendarWidget *date;
    QLineEdit *l_name;
    QTimeEdit *time;

    bool is_with_name;
    bool is_with_time;

public:
    explicit UDateDialog(bool with_name = false, bool with_time = false, const QString &current = "");

    static QString getDate(bool with_name, bool with_time, const QString &current = "");

protected:
    void fromString(const QString &name);

    QString toString();
};


#endif //ORGANIZER_UDATEWIDGET_H
