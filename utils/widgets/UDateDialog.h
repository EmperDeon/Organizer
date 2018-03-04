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
#include <utils/widgets/dates/UDateItem.h>
#include "UDatesWidget.h"

class UDatesWidget;

class UDateItem;


class UDateDialog : public QDialog {
    QCalendarWidget *date;
    QLineEdit *l_name;

    bool is_with_name;

public:
    explicit UDateDialog(bool with_name = false, UDateItem *item = nullptr);

    static QString setDate(UDatesWidget *wgt, UDateItem *item);
};


#endif //ORGANIZER_UDATEWIDGET_H
