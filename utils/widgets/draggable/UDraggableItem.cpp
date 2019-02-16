/*
	Copyright (c) 2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QApplication>
#include <QtGui/QDrag>
#include <QtWidgets/QStyle>
#include <QtCore/QMimeData>
#include <utils/logs/ULogger.h>
#include "UDraggableItem.h"

UDraggableItem::UDraggableItem(unsigned long id) : item_id(id) {
    setAcceptDrops(true);
    topMargin = new QSpacerItem(0, 0);
    bottomMargin = new QSpacerItem(0, 0);

    marginLayout = new QVBoxLayout;
    marginLayout->addSpacerItem(topMargin);
    setLayout(marginLayout);
}

void UDraggableItem::addLayout(QBoxLayout *l) {
    marginLayout->addLayout(l);
    marginLayout->addSpacerItem(bottomMargin);
}

bool UDraggableItem::eventFilter(QObject *watched, QEvent *event) {
    static QObject *object = nullptr;
    static QPoint drag_start_position;

    if (object != watched) {
        object = watched;
        drag_start_position = QPoint();
    }

    auto *m_event = static_cast<QMouseEvent *>(event);

    auto alt_pressed = QGuiApplication::queryKeyboardModifiers().testFlag(Qt::AltModifier);
    if (!alt_pressed) {
        return itemEventFilter(watched, event);
    }

    if (event->type() == QEvent::MouseButtonPress) {
        if (m_event->button() == Qt::LeftButton)
            drag_start_position = m_event->pos();

        return true;

    } else if (event->type() == QEvent::MouseMove) {
        if (!(m_event->buttons() & Qt::LeftButton))
            return false;

        if ((m_event->pos() - drag_start_position).manhattanLength() < QApplication::startDragDistance())
            return false;

        QDrag *drag = new QDrag(this);

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("id", QString::number(item_id).toUtf8());

        drag->setPixmap(this->grab());
        drag->setMimeData(mimeData);

        drag->exec();

        return true;

    } else {
        return itemEventFilter(watched, event);
    }
}

bool UDraggableItem::itemEventFilter(QObject *watched, QEvent *event) {
    return QObject::eventFilter(watched, event);
}

void UDraggableItem::itemDropped(unsigned long, unsigned long) {
    logW("Not implemented");
}

void UDraggableItem::setMarginFromPos(int py) {
    if (py < 5 || py > this->height() - 5) {
        topMargin->changeSize(0, 0);
        bottomMargin->changeSize(0, 0);

    } else if (py <= (this->height() / 2)) {
        topMargin->changeSize(0, 20);
        bottomMargin->changeSize(0, 0);

    } else {
        topMargin->changeSize(0, 0);
        bottomMargin->changeSize(0, 20);
    }

    marginLayout->invalidate();
}

void UDraggableItem::installDragFilter(QList<QWidget *> list) {
    installEventFilter(this);

    for (auto *wgt : list) {
        wgt->installEventFilter(this);
    }
}

void UDraggableItem::dragEnterEvent(QDragEnterEvent *event) {
    event->acceptProposedAction();
}

void UDraggableItem::dragMoveEvent(QDragMoveEvent *event) {
    setMarginFromPos(event->pos().y());
}

void UDraggableItem::dragLeaveEvent(QDragLeaveEvent *) {
//    Causes widget to flicker, gets triggered in middle of the widget (possibly, because of layout invalidation)
//    setMarginFromPos(-1);
}

void UDraggableItem::dropEvent(QDropEvent *event) {
    unsigned long next_id = item_id + ((event->pos().y() <= this->height() / 2) ? 0 : 1),
            dropped_id = (unsigned long) QString::fromUtf8(event->mimeData()->data("id")).toLong();

    logD("Dropped " + QString::number(dropped_id) + " at " + QString::number(next_id));

    if (dropped_id == item_id || dropped_id == (item_id + 1)) {
        logI("Item dropped on self");
    } else {
        itemDropped(dropped_id, next_id);
    }

    setMarginFromPos(-1);
}
