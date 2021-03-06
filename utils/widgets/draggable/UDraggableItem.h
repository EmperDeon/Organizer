/*
	Copyright (c) 2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_UDRAGGABLEITEM_H
#define ORGANIZER_UDRAGGABLEITEM_H

#include <QtWidgets/QFrame>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QVBoxLayout>


class UDraggableItem : public QWidget {
    unsigned long item_id;
    QVBoxLayout *marginLayout;
    QSpacerItem *topMargin, *bottomMargin;

public:
    UDraggableItem(unsigned long id);

    bool eventFilter(QObject *watched, QEvent *event) override;

    // For child event handling
    virtual bool itemEventFilter(QObject *watched, QEvent *event);

    virtual void itemDropped(unsigned long dropped_id, unsigned long at_id);

protected:
    void addLayout(QBoxLayout *l);

    void setMarginFromPos(int py);

    void installDragFilter(QList<QWidget *> list);

    void dragEnterEvent(QDragEnterEvent *event) override;

    void dragMoveEvent(QDragMoveEvent *event) override;

    void dragLeaveEvent(QDragLeaveEvent *event) override;

    void dropEvent(QDropEvent *event) override;
};


#endif //ORGANIZER_UDRAGGABLEITEM_H
