/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QLabel>
#include <QtWidgets/QMenu>
#include <utils/UScrollArea.h>
#include <QtWidgets/QPushButton>
#include "UDatesWidget.h"
#include "UDateDialog.h"
#include <QDebug>
#include <QtWidgets/QtWidgets>

UDatesWidget::UDatesWidget() {
    auto *l = new QVBoxLayout;

    layout = new QVBoxLayout;
    auto *scroll = new UScrollArea(layout);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);

    auto *b_add = new QPushButton(tr("Create"));
    b_add->setProperty("newLineButton", "true");

    connect(b_add, &QPushButton::clicked, this, &UDatesWidget::createDate);

    layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);
    l->setMargin(0);
    l->setContentsMargins(0, 0, 0, 0);

    l->addWidget(b_add, 0, Qt::AlignTop);
    l->addSpacing(5);
    l->addWidget(scroll);

    setLayout(l);
}

void UDatesWidget::load(const QMap<QString, UDateItem *> &l) {
    for (int i = 0; i < layout->count(); i++)
        layout->takeAt(0)->widget()->deleteLater();

    for (const QString &id : l.keys()) {
        addItem(l[id]);
    }
}

void UDatesWidget::addItem(UDateItem *item) {
    connect(item, &UDateItem::edit, this, &UDatesWidget::changeDate);
    connect(item, &UDateItem::remove, this, &UDatesWidget::removeDate);
    connect(item, &UDateItem::select, this, &UDatesWidget::selectDate);

    layout->addWidget(item);

    items[item->id()] = item;
}

void UDatesWidget::findAndDo(const QString &id, const std::function<void(UDateItem *item)> &func) {
    if (items.contains(id)) {
        func(items[id]);
    }
}

void UDatesWidget::createDate() {
    auto *item = new UDateItem("", "", {});
    UDateDialog::setDate(this, item);

    if (!item->id().isEmpty())
            emit createdDate(item);
}

void UDatesWidget::changeDate(QString id) {
    QString new_id;
    auto *item = items.value(id, nullptr);

    new_id = UDateDialog::setDate(this, item);

    if (new_id.isEmpty()) {
        return;
    }

    if (current_id == id)
        current_id = new_id;

    emit changedDate(id, item);
}

void UDatesWidget::removeDate(const QString &id) {
    QString next_id;

    if (items.size() == 1) {
//        qDebug() << "Destroyed last entry";

    } else if (items.lastKey() == id) { // Set pre-last item active
        next_id = items.keys()[items.keys().size() - 2];

    } else if (items.firstKey() == id) {
        next_id = items.keys()[1];

    } else {
        next_id = items.keys()[items.keys().indexOf(id) - 1];
    }

//    qDebug() << "Deleting id: " << id << ", next_selected: " << next_id;

    if (next_id == "")
        selectDate(next_id);

    if (items.contains(id)) {
        emit removedDate(id);

        items[id]->deleteLater();
        items.remove(id);
    }
}

void UDatesWidget::selectDate(const QString &id) {
    emit selectedDate(current_id, id);

    if (!current_id.isEmpty()) {
        findAndDo(current_id, [](UDateItem *item) { item->setActive(false); });
    }

    current_id = id;
    findAndDo(current_id, [](UDateItem *item) { item->setActive(true); });
}

/*
 * Insert new item
 * If items already contain this date, increment secs by 1
 * */
QString UDatesWidget::insertNewDate(const QDate &new_date, const QString &old_id) {
//    qDebug() << "New: " << new_date << ", old: " << old_id;

    QDateTime date(new_date);
    QString new_id = QString::number(date.toSecsSinceEpoch());

    while (items.contains(new_id) && new_id != old_id) {
        date = date.addSecs(1);
        new_id = QString::number(date.toSecsSinceEpoch());

//        qDebug() << date.toSecsSinceEpoch() << items.contains(new_id) << (new_id != old_id);
    }

    if (new_id != old_id && !old_id.isEmpty()) {
        items[new_id] = items[old_id];
        items.remove(old_id);

//        qDebug() << "Moving " << new_id;
    }

//    qDebug() << "Result id: " << new_id;

    return new_id;
}
