/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "UTreeWidget.h"
#include "QtWidgets/QInputDialog"

UTreeWidget::UTreeWidget() : QTreeWidget() {
    connect(this, &UTreeWidget::itemExpanded, this, &UTreeWidget::resizeColumns);
}

void UTreeWidget::addRoot(const QString &text) {
    auto *t_root = new UTreeItem({text});
    addTopLevelItem(t_root);
}

UTreeItem *UTreeWidget::addToRoot(const QStringList &list) {
    return new UTreeItem(topLevelItem(0), list);
}

void UTreeWidget::moveItem(UTreeItem *from, UTreeItem *to) {
    UTreeItem *cur_parent = from->parent(), *sel_parent = to->parent();

    UTreeItem *cur = cur_parent->takeChild(cur_parent->indexOfChild(from));
    sel_parent->insertChild(sel_parent->indexOfChild(to), cur);
}

void UTreeWidget::renameItem(UTreeItem *item, int column) {
    const QString &text = QInputDialog::getText(this, tr("Tree item editing"), tr("Enter new text: "),
                                                QLineEdit::Normal,
                                                item->data(column, Qt::DisplayRole).toString()
    );

    if (!text.isEmpty()) {
        item->setData(column, Qt::DisplayRole, text);
    }
}

void UTreeWidget::mousePressEvent(QMouseEvent *event) {
    QTreeView::mousePressEvent(event);
}

void UTreeWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (!is_movable) {
        return;
    }

    if (current_item != nullptr) {
        current_item = nullptr;
    }

    setCursor(QCursor(Qt::ArrowCursor));
}

void UTreeWidget::mouseMoveEvent(QMouseEvent *event) {
    if (!is_movable) {
        return;
    }

    if (current_item == nullptr) {
        setCursor(QCursor(Qt::DragMoveCursor));

        current_item = selectedItems().first();
    } else {
        UTreeItem *selected_item = itemAt(event);

        if (selected_item == nullptr || current_item == selected_item
            || levelOfItem(current_item) != levelOfItem(selected_item)) {
            return;
        }

        moveItem(current_item, selected_item);
    }
}

void UTreeWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    if (!is_editable) {
        return;
    }

    UTreeItem *item = itemAt(event);

    if (item != nullptr) {
        renameItem(item, columnAt(event));
    }
}

int UTreeWidget::levelOfItem(UTreeItem *item) {
    int i = 0;

    while (item != nullptr && item->parent() != nullptr) {
        item = item->parent();
        i++;
    }

    return i;
}

UTreeItem *UTreeWidget::itemAt(QMouseEvent *event) {
    return QTreeWidget::itemAt(event->localPos().toPoint());
}

int UTreeWidget::columnAt(QMouseEvent *event) {
    return QTreeWidget::columnAt(event->localPos().toPoint().x());
}

void UTreeWidget::resizeColumns() {
    if (is_auto_resize) {
        for (int i = 0; i < columnCount() - 1; i++) // resize all but last column
            resizeColumnToContents(i);
    }
}
