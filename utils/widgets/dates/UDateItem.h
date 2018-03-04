/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_UDATEITEM_H
#define ORGANIZER_UDATEITEM_H

#include <QtWidgets/QFrame>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMenu>


class UDateItem : public QFrame {
Q_OBJECT

    QVBoxLayout *layout;
    QString i_id, i_name;
    QStringList i_lines;
    QMenu *context_menu;

public:
    explicit UDateItem(const QString &id, const QString &nm, const QStringList &lines);

    const QString &id() { return i_id; }

    const QString &name() { return i_name; }

    const QStringList &lines() { return i_lines; }

    void setActive(bool active);

    void setContents(const QString &id, const QString &nm, const QStringList &lines = {});

protected:
    void edit_item();

    void remove_item();

    void mouseReleaseEvent(QMouseEvent *event) override;

    QString id_to_name(const QString &id, const QString &name);

Q_SIGNALS:

    void select(const QString &id);

    void edit(QString id);

    void remove(const QString &id);
};


#endif //ORGANIZER_UDATEITEM_H
