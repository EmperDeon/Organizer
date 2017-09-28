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

	for (auto *line : lines) {
		r += line->text() + "\n";
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

	for (auto *line : lines) {
		r << line->text();
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
	lines << line;
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
	int i = lines.indexOf(l);

	if (i != -1) {
		if (i == lines.count() - 1)
			addLine();
		lines.value(i + 1)->setFocus();
	}
}

void MLsTab::arrowPressed(QLineEdit *l, bool up) {
	int i = lines.indexOf(l);

	if (i != -1) {
		if (!up && i < list->count() - 1)
			lines.value(i + 1)->setFocus();
		else if (up && i > 0)
			lines.value(i - 1)->setFocus();
	}
}


// MListEF
bool MListEF::eventFilter(QObject *object, QEvent *event) {
	auto *e = dynamic_cast<QLineEdit *>(object);

	if (e != nullptr) {
		if (event->type() == QEvent::MouseButtonRelease) {
			if (dynamic_cast<QMouseEvent *>(event)->button() == Qt::RightButton) {
				tab->delChild(e);

				event->accept();
				return true;
			}

		} else if (event->type() == QEvent::KeyRelease) {
			auto *ke = dynamic_cast<QKeyEvent *>(event);
			switch (ke->key()) {

				case Qt::Key_Return:
					tab->returnPressed(e);
					event->accept();
					return true;

				case Qt::Key_Backspace:
					if (e->text() == "") {
						tab->delChild(e);
						event->accept();
						return true;
					}
					break;

				case Qt::Key_Up:
					tab->arrowPressed(e, true);
					event->accept();
					return true;

				case Qt::Key_Down:
					tab->arrowPressed(e, false);
					event->accept();
					return true;

				default:;
			}

			tab->updated();
		}
	}

	return QObject::eventFilter(object, event);
}
// MListEF