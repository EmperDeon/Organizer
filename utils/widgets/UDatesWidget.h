/*
	Copyright (c) 2017 by Ilya Barykin
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

class UDateItem;

class UDatesWidget : public QWidget {
Q_OBJECT

    QVBoxLayout *layout;

    bool is_with_name = false;
    bool is_with_time = false;
    bool is_reverse = false;

    QString current_item;
    QMap<QString, UDateItem *> items;

public:
    UDatesWidget();

    bool withName() { return is_with_name; }

    void setWithName(bool n) { is_with_name = n; }

    bool withTime() { return is_with_time; }

    void setWithTime(bool t) { is_with_time = t; }

    bool reverse() { return is_reverse; }

    void setReverse(bool r) { is_reverse = r; }

    QString currentDate() { return current_item; }

    void load(const QMap<QString, QStringList> &l);

    void selectDate(const QString &name);

protected:
    void addItem(const QString &name, const QStringList &lines);

    // Find by name and exec function
    void findAndDo(const QString &name, const std::function<void(UDateItem *item)> &func);

    // Slots
    void createDate();

    void changeDate(const QString &name, const QStringList &lines = {});

    void removeDate(const QString &name);

Q_SIGNALS:

    void createdDate(const QString &name);

    void changedDate(const QString &name);

    void removedDate(const QString &name);

    void selectedDate(const QString &from, const QString &to);
};


class UDateItem : public QFrame {
Q_OBJECT

    QVBoxLayout *layout;
    QString i_name;
    QMenu *context_menu;

public:
    explicit UDateItem(const QString &nm, const QStringList &lines);

    QString name() { return i_name; }

    void setActive(bool active);

    void setContents(const QString &nm, const QStringList &lines = {});

protected:
    void edit_item();

    void remove_item();

    void mouseReleaseEvent(QMouseEvent *event) override;

Q_SIGNALS:

    void select(const QString &name);

    void edit(const QString &name, const QStringList &lines);

    void remove(const QString &name);
};

#endif //ORGANIZER_UDATESWIDGET_H
