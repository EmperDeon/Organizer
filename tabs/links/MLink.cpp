#include <QtGui/QDesktopServices>
#include <QtCore/QEvent>
#include <QtCore/QUrl>
#include "MLink.h"

MLink::MLink(MGroup *g, QJsonObject o) : gr(g) {
	name = o["name"].toString();
	link = o["link"].toString();

	auto *l = new QVBoxLayout;

	lN = new QLineEdit(name);
	lL = new QLineEdit(link);

	lL->setProperty("link", "true");
	lL->installEventFilter(this);

	connect(lN, &QLineEdit::textChanged, this, &MLink::editChange);
	connect(lL, &QLineEdit::textChanged, this, &MLink::editChange);

	l->addWidget(lN);
	l->addWidget(lL);

	setContextMenuPolicy(Qt::NoContextMenu);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	setLayout(l);
}

void MLink::editChange() {
	empty = lN->text() == "" && lL->text() == "";
	name = lN->text();
	link = lL->text();

	gr->updateLinks();
}

QJsonObject MLink::getJson() const {
	return QJsonObject{{"name", name},
	                   {"link", link}};
}

bool MLink::eventFilter(QObject *object, QEvent *event) {
	if (event->type() == QEvent::MouseButtonDblClick) {
		QDesktopServices::openUrl(link);
	}

	return QObject::eventFilter(object, event);
}
