/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_WTGROUPLABEL_H
#define ORGANIZER_WTGROUPLABEL_H

#include <QtWidgets/QLabel>
#include <QtCore/QEvent>
#include "WTGroups.h"

class WTGroups;

class WTGroupLabel : public QWidget {
    WTGroups *groups;
    QLabel *label;

public:
    explicit WTGroupLabel(WTGroups *w);

    void setGroup(const QString &group);

    void cycleGroups();

    bool eventFilter(QObject *watched, QEvent *event) override;
};


#endif //ORGANIZER_WTGROUPLABEL_H
