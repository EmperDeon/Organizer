/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QLabel>
#include <QtWidgets/QMenu>
#include <QtWidgets/QStyle>
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

void UDatesWidget::load(const QMap<QString, QStringList> &l) {
    for (int i = 0; i < layout->count(); i++)
        layout->takeAt(0)->widget()->deleteLater();

    for (const QString &name : l.keys()) {
        addItem(name, l[name]);
    }
}

void UDatesWidget::addItem(const QString &name, const QStringList &lines) {
    auto *item = new UDateItem(name, lines);

    connect(item, &UDateItem::edit, this, &UDatesWidget::changeDate);
    connect(item, &UDateItem::remove, this, &UDatesWidget::removeDate);
    connect(item, &UDateItem::select, this, &UDatesWidget::selectDate);

    if (is_reverse) {
        layout->insertWidget(0, item);
    } else {
        layout->addWidget(item);
    }

    items[name] = item;
}

void UDatesWidget::findAndDo(const QString &name, const std::function<void(UDateItem *item)> &func) {
//    qDebug() << items.contains(name) << (dynamic_cast<QWidget *>(items[name]) == nullptr);

    if (items.contains(name)) {
        func(items[name]);
    }
}

void UDatesWidget::createDate() {
    QString date = UDateDialog::getDate(is_with_name, is_with_time);

    if (!date.isEmpty())
            emit createdDate(date);
}

void UDatesWidget::changeDate(const QString &name, const QStringList &lines) {
    QString new_name;

    if (lines.size() > 0 && lines[0] == "date_edit") {
        new_name = UDateDialog::getDate(is_with_name, is_with_time, name);

        items[new_name] = items[name];
        items.remove(name);

        emit changedDate(name, new_name);

    } else {
        new_name = name;
    }

    findAndDo(new_name, [new_name, lines](UDateItem *item) { item->setContents(new_name, lines); });
}

void UDatesWidget::removeDate(const QString &name) {
    QString next_item;
    if (items.lastKey() == name) { // Set pre-last item active
        next_item = items.keys()[items.keys().size() - 2];

    } else if (items.firstKey() == name) {
        next_item = items.keys()[1];

    } else {
        next_item = items.keys()[items.keys().indexOf(name) - 1];
    }

    emit removedDate(name);
    selectDate(next_item);

    findAndDo(name, [](UDateItem *item) { item->deleteLater(); });
}

void UDatesWidget::selectDate(const QString &name) {
    emit selectedDate(current_item, name);

    if (!current_item.isEmpty()) {
        findAndDo(current_item, [](UDateItem *item) { item->setActive(false); });
    }

    current_item = name;
    findAndDo(current_item, [](UDateItem *item) { item->setActive(true); });
}


UDateItem::UDateItem(const QString &nm, const QStringList &lines) : i_name(nm) {
    layout = new QVBoxLayout;

    setContents(nm, lines);

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    // Menu
    context_menu = new QMenu;
    context_menu->addAction("Edit", this, &UDateItem::edit_item);
    context_menu->addAction("Delete", this, &UDateItem::remove_item);

    setLayout(layout);
}

void UDateItem::edit_item() {
    emit edit(i_name, {"date_edit"});
}

void UDateItem::remove_item() {
    emit remove(i_name);
}

void UDateItem::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        context_menu->exec(event->globalPos()); // Show context menu
    } else {
        emit select(i_name);
    }
}

void UDateItem::setActive(bool active) {
    setProperty("active_item", active ? "true" : "false");
    style()->unpolish(this);
    style()->polish(this);
}

void UDateItem::setContents(const QString &nm, const QStringList &lines) {
    for (int i = 0; i < layout->count(); i++)
        layout->takeAt(0)->widget()->deleteLater();

    auto *first_line = new QLabel(i_name);
    first_line->setProperty("class", "first_line");

    layout->addWidget(first_line);

    for (const QString &line : lines) {
        layout->addWidget(new QLabel(line));
    }

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}
