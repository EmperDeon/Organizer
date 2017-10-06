/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtGui/QDesktopServices>
#include <QtCore/QEvent>
#include <QtCore/QUrl>
#include "MLink.h"

MLink::MLink(MGroup *g, QJsonObject o) : group(g) {
    auto *l = new QVBoxLayout;

    l_name = new QLineEdit(o["name"].toString());
    l_link = new QLineEdit(o["link"].toString());

    l_link->setProperty("link", "true");
    l_link->installEventFilter(this);

    connect(l_name, &QLineEdit::textChanged, this, &MLink::editChange);
    connect(l_link, &QLineEdit::textChanged, this, &MLink::editChange);

    l->addWidget(l_name);
    l->addWidget(l_link);

    setContextMenuPolicy(Qt::NoContextMenu);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setLayout(l);
}

void MLink::editChange() {
    empty = l_name->text() == "" && l_link->text() == "";

    group->updateLinks();
}

QJsonObject MLink::getJson() const {
    return QJsonObject{{"name", l_name->text()},
                       {"link", l_link->text()}};
}

bool MLink::eventFilter(QObject *object, QEvent *event) {
    if (event->type() == QEvent::MouseButtonDblClick) {
        QDesktopServices::openUrl(l_link->text());
    }

    return QObject::eventFilter(object, event);
}
