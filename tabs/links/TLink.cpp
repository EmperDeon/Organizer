/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtGui/QDesktopServices>
#include <QtCore/QEvent>
#include <QtCore/QUrl>
#include "TLink.h"

TLink::TLink(TLinksGroup *g, json_o o) : group(g) {
    auto *l = new QVBoxLayout;

    l_name = new QLineEdit(o["name"].get<QString>());
    l_link = new QLineEdit(o["link"].get<QString>());

    l_link->setProperty("link", "true");
    l_link->installEventFilter(this);

    connect(l_name, &QLineEdit::textChanged, this, &TLink::editChange);
    connect(l_link, &QLineEdit::textChanged, this, &TLink::editChange);

    l->addWidget(l_name);
    l->addWidget(l_link);

    setContextMenuPolicy(Qt::NoContextMenu);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setLayout(l);
}

void TLink::editChange() {
    empty = l_name->text() == "" && l_link->text() == "";

    group->updateLinks();
}

json_o TLink::getJson() const {
    return json_o{{"name", l_name->text()},
                  {"link", l_link->text()}};
}

bool TLink::eventFilter(QObject *object, QEvent *event) {
    if (event->type() == QEvent::MouseButtonDblClick) {
        QDesktopServices::openUrl(l_link->text());
    }

    return QObject::eventFilter(object, event);
}
