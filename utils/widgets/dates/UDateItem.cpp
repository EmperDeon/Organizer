/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QStyle>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QLabel>
#include <QtCore/QDateTime>
#include <vars.h>
#include <utils/Utils.h>
#include <vendor/verdigris/src/wobjectimpl.h>
#include "UDateItem.h"

UDateItem::UDateItem(const QString &id, const QString &nm, const QStringList &lines) : i_id(id) {
    layout = new QVBoxLayout;

    setContents(id, nm, lines);

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    // Menu
    context_menu = new QMenu;
    context_menu->addAction("Edit", this, &UDateItem::edit_item);
    context_menu->addAction("Delete", this, &UDateItem::remove_item);

    setLayout(layout);
}

void UDateItem::edit_item() {
    emit edit(i_id);
}

void UDateItem::remove_item() {
    emit remove(i_id);
}

void UDateItem::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        context_menu->exec(event->globalPos()); // Show context menu
    } else {
        emit select(i_id);
    }
}

void UDateItem::setActive(bool active) {
    setProperty("active_item", active ? "true" : "false");
    style()->unpolish(this);
    style()->polish(this);
}

void UDateItem::setContents(const QString &id, const QString &nm, const QStringList &lines) {
    i_id = id;
    i_name = nm;
    i_lines = lines;

    for (int i = 0; i < layout->count(); i++)
        layout->takeAt(0)->widget()->deleteLater();

    auto *first_line = new QLabel(id_to_name(id, nm));
    first_line->setProperty("class", "first_line");

    layout->addWidget(first_line);

    for (const QString &line : lines) {
        if (line != "date_edit")
            layout->addWidget(new QLabel(line));
    }
}

QString UDateItem::id_to_name(const QString &id, const QString &name) {
    auto date = Utils::dateFromString(id);
    return QString("%1 %2").arg(date.toString(DATE_FORMAT)).arg(name);
}

W_OBJECT_IMPL(UDateItem)