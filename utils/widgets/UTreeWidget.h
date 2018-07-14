/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_UTREEWIDGET_H
#define ORGANIZER_UTREEWIDGET_H

#include <QtWidgets/QTreeWidget>
#include <QtGui/QtEvents>


typedef QTreeWidgetItem UTreeItem;

class UTreeWidget : public QTreeWidget {
    UTreeItem *current_item = nullptr;

    bool is_movable = false;
    bool is_editable = false;
    bool is_auto_resize = false;

public:
    UTreeWidget();

    void addRoot(const QString &text);

    UTreeItem *addToRoot(const QStringList &list);

    void moveItem(UTreeItem *from, UTreeItem *to);

    void renameItem(UTreeItem *item, int column);

    int levelOfItem(UTreeItem *item);


    bool movable() { return is_movable; }

    bool editable() { return is_editable; }

    bool autoResize() { return is_auto_resize; }

    void setMovable(bool m) { is_movable = m; }

    void setEditable(bool e) { is_editable = e; }

    void setAutoResizable(bool a) { is_auto_resize = a; }

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override;

    UTreeItem *itemAt(QMouseEvent *event);

    int columnAt(QMouseEvent *event);

    void resizeColumns();
};


#endif //ORGANIZER_UTREEWIDGET_H
