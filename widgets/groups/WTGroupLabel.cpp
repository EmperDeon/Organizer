/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "WTGroupLabel.h"

WTGroupLabel::WTGroupLabel(WTGroups *w) : groups(w) {
    auto *l = new QHBoxLayout;

    auto *label = new QLabel(QObject::tr("Current group:"));
    current = new QLabel;

    l->setContentsMargins(0, 10, 0, 10);

    l->addWidget(label);
    l->addWidget(current);

    label->installEventFilter(this);
    current->installEventFilter(this);

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setLayout(l);
}

void WTGroupLabel::setGroup(const QString &group) {
    current->setText(group);
}

void WTGroupLabel::cycleGroups() {
    groups->tabs->cycleGroup();
}

bool WTGroupLabel::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::MouseButtonRelease) {
//        qDebug() << "Clicked group cycle";

        cycleGroups();
        return true;
    } else {
        return QObject::eventFilter(watched, event);
    }
}
