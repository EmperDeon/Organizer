/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "WTGroupLabel.h"

WTGroupLabel::WTGroupLabel(WTGroups *w) : groups(w) {
    auto *l = new QHBoxLayout;

    label = new QLabel;

    l->setContentsMargins(0, 10, 0, 10);

    l->addWidget(new QLabel(QObject::tr("Current group:")));
    l->addWidget(label);

    label->installEventFilter(this);

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setLayout(l);
}

void WTGroupLabel::setGroup(const QString &group) {
    label->setText(group);
}

void WTGroupLabel::cycleGroups() {
    groups->tabs->cycleGroup();
}

bool WTGroupLabel::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::MouseButtonRelease) {
//        qDebug() << "Clicked group cycle";

        cycleGroups();

    } else {
        return QObject::eventFilter(watched, event);
    }
}
