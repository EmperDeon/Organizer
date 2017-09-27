#include "MLsTab.h"
#include <QtWidgets/QMessageBox>
#include <QtCore/QEvent>
#include <QtGui/QMouseEvent>

MLsTab::MLsTab(const QJsonObject &o) : MTab(o, MTab::List) {
	auto *l = new QVBoxLayout;

	list = new QVBoxLayout;
	events = new MListEF(this);

	list->setAlignment(Qt::AlignTop);

	auto *scroll = new UScrollArea(list);

	l->addWidget(scroll);
	l->setMargin(0);

	setLayout(l);

	load();
}

QString MLsTab::getDesc() {
	return "List: " + name;
}

void MLsTab::importFrom(QString s) {
	for (const QString &t : s.split('\n')) {
		addLine(t);
	}
}

QString MLsTab::exportTo() {
	QString r;

	for (int i = 0; i < list->count(); i++) {
		QLineEdit *edit = (reinterpret_cast<QLineEdit *>(list->itemAt(i)->widget()));
		if (edit != nullptr)
			r += edit->text() + "\n";
	}

	return r;
}

void MLsTab::fromJson(QJsonValue v) {
	QJsonArray arr = v.toArray();

	for (QJsonValue t : arr)
		addLine(t.toString());

	if (arr.empty())
		addLine();
}

QJsonValue MLsTab::toJson() {
	QJsonArray r;
	for (int i = 0; i < list->count(); i++) {
		QString t = (reinterpret_cast<QLineEdit *>(list->itemAt(i)->widget()))->text();
		if (t != "") r << t;
	}

	return r;
}

void MLsTab::addLine(QString text) {
	auto *line = new QLineEdit;
	line->setProperty("listItem", "true");
	line->setText(text);
	line->installEventFilter(events);
	line->setContextMenuPolicy(Qt::NoContextMenu);
	line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	list->addWidget(line);
}

void MLsTab::delChild(QLineEdit *t) {

	if (t != nullptr &&
	    QMessageBox::question(this, tr("Delete line ?"), tr("Delete line ?") + "\n\'" + t->text() + '\'') ==
	    QMessageBox::Yes) {
		list->removeWidget(t);
		delete t;

	}
}

void MLsTab::returnPressed(QLineEdit *l) {
	for (int i = 0; i < list->count(); i++) {
		QLineEdit *edit = (static_cast<QLineEdit *>(list->itemAt(i)->widget()));

		if (l == edit) {
			if (i == list->count() - 1)
				addLine();
			getLineEdit(i + 1)->setFocus();
		}
	}
}

void MLsTab::arrowPressed(QLineEdit *l, bool up) {
	for (int i = 0; i < list->count(); i++) {
		QLineEdit *edit = getLineEdit(i);

		if (l == edit) {
			if (!up && i < list->count() - 1)
				getLineEdit(i + 1)->setFocus();
			else if (up && i > 0)
				getLineEdit(i - 1)->setFocus();
		}
	}
}

QLineEdit *MLsTab::getLineEdit(int i) const {
	return (static_cast<QLineEdit *>(list->itemAt(i)->widget()));
}


// MListEF
bool MListEF::eventFilter(QObject *object, QEvent *event) {
	QLineEdit *e;

	if ((e = static_cast<QLineEdit *>(object)) != nullptr) {
		if (event->type() == QEvent::MouseButtonRelease) {
			if (static_cast<QMouseEvent *>(event)->button() == Qt::RightButton) {
				par->delChild(e);

				event->accept();
				return true;
			}
		} else if (event->type() == QEvent::KeyRelease) {
			auto *ke = static_cast<QKeyEvent *>(event);
			switch (ke->key()) {

				case Qt::Key_Return:
					par->returnPressed(e);
					event->accept();
					return true;

				case Qt::Key_Backspace:
					if (e->text() == "") {
						par->delChild(e);
						event->accept();
						return true;
					}
					break;

				case Qt::Key_Up:
					par->arrowPressed(e, true);
					event->accept();
					return true;

				case Qt::Key_Down:
					par->arrowPressed(e, false);
					event->accept();
					return true;

				default:;
			}

			par->updated();
		}
	}

	return QObject::eventFilter(object, event);
}
// MListEF