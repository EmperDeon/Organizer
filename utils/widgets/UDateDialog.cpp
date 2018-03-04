/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <crypt/CTools.h>
#include "UDateDialog.h"

UDateDialog::UDateDialog(bool with_name, UDateItem *item) : is_with_name(with_name) {
    auto *l = new QVBoxLayout;

    date = new QCalendarWidget;
    l_name = new QLineEdit;


    date->setMaximumDate(QDate::currentDate());

    l->addWidget(date);

    if (is_with_name)
        l->addWidget(l_name);

    auto *h_l = new QHBoxLayout;
    QPushButton *b_acc = new QPushButton("OK"), *b_rej = new QPushButton("Cancel");

    h_l->addWidget(b_acc);
    h_l->addWidget(b_rej);
    l->addLayout(h_l);

    if (item != nullptr && !item->id().isEmpty()) {
        date->setSelectedDate(CTools::dateFromString(item->id()));
        l_name->setText(item->name());
    }

    connect(b_acc, &QPushButton::clicked, this, &UDateDialog::accept);
    connect(b_rej, &QPushButton::clicked, this, &UDateDialog::reject);

    setLayout(l);
}

QString UDateDialog::setDate(UDatesWidget *wgt, UDateItem *item) {
    auto *d = new UDateDialog(wgt->withName(), item);

    if (d->exec()) {
        QString new_id = wgt->insertNewDate(d->date->selectedDate(), item->id());
        item->setContents(new_id, d->l_name->text(), item->lines());

        return new_id;

    } else {
        return "";
    }
}
