/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_UDATESWIDGET_H
#define ORGANIZER_UDATESWIDGET_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QVBoxLayout>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QMenu>
#include <functional>
#include <utils/widgets/dates/UDateItem.h>
#include <vendor/verdigris/src/wobjectdefs.h>


class UDateItem;

W_REGISTER_ARGTYPE(UDateItem)
W_REGISTER_ARGTYPE(UDateItem*)
W_REGISTER_ARGTYPE(QString)

class UDatesWidget : public QWidget {
    W_OBJECT(UDatesWidget)

    QVBoxLayout *layout;

    bool is_with_name = false;
    bool is_reverse = false;

    QString current_id;
    QMap<QString, UDateItem *> items;

public:
    UDatesWidget();

    bool withName() { return is_with_name; }

    void setWithName(bool n) { is_with_name = n; }

    bool reverse() { return is_reverse; }

    void setReverse(bool r) { is_reverse = r; }

    QString currentDate() { return current_id; }

    UDateItem *currentDateItem() { return items.value(current_id, nullptr); }

    void load(const QMap<QString, UDateItem *> &l);

    void selectDate(const QString &id);

    void addItem(UDateItem *item);

protected:
    // Find by name and exec function
    void findAndDo(const QString &id, const std::function<void(UDateItem *item)> &func);

    // Slots
    void createDate();

    void changeDate(QString id);

    void removeDate(const QString &id);

    QString insertNewDate(const QDate &new_date, const QString &old_id);

public /* signals */:
    void createdDate(UDateItem *item) W_SIGNAL(createdDate, item)

    // Called even if id isn't changed, because name could be changed
    void changedDate(const QString &old_id, UDateItem *item) W_SIGNAL(changedDate, old_id, item)

    void removedDate(const QString &id) W_SIGNAL(removedDate, id)

    void selectedDate(const QString &from, const QString &to) W_SIGNAL(selectedDate, from, to)

    friend class UDateDialog;
};

#endif //ORGANIZER_UDATESWIDGET_H
