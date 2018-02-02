/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <vars.h>
#include <QtWidgets/QDialog>
#include "UDateDialog.h"

UDateDialog::UDateDialog(bool with_name, bool with_time, const QString &current) : is_with_name(with_name),
                                                                                   is_with_time(with_time) {
    auto *l = new QVBoxLayout;

    date = new QCalendarWidget;
    time = new QTimeEdit;
    l_name = new QLineEdit;


    date->setMaximumDate(QDate::currentDate());

    l->addWidget(date);

    if (is_with_time)
        l->addWidget(time);
    if (is_with_name)
        l->addWidget(l_name);

    auto *h_l = new QHBoxLayout;
    QPushButton *b_acc = new QPushButton("OK"), *b_rej = new QPushButton("Cancel");

    h_l->addWidget(b_acc);
    h_l->addWidget(b_rej);
    l->addLayout(h_l);

    connect(b_acc, &QPushButton::clicked, this, &UDateDialog::accept);
    connect(b_rej, &QPushButton::clicked, this, &UDateDialog::reject);

    setLayout(l);
}

QString UDateDialog::getDate(bool with_name, bool with_time, const QString &current) {
    auto *d = new UDateDialog(with_name, with_time, current);
    d->fromString(current);

    if (d->exec()) {
        return d->toString();

    } else {
        return "";
    }
}

void UDateDialog::fromString(const QString &name) {
    if (name.isEmpty())
        return;

    QStringList args = name.split(' ');
    date->setSelectedDate(QDate::fromString(args.takeFirst(), DATE_FORMAT));

    if (is_with_time)
        time->setTime(QTime::fromString(args.takeFirst(), TIME_FORMAT));

    if (is_with_name)
        l_name->setText(args.join(' '));
}

QString UDateDialog::toString() {
    QStringList args;
    args << date->selectedDate().toString(DATE_FORMAT);

    if (is_with_time)
        args << time->time().toString(TIME_FORMAT);

    if (is_with_name)
        args << l_name->text();

    return args.join(' ');
}
