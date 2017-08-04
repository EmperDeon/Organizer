#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "MNewGr.h"

MNewGr::MNewGr(MWindow *w, MLinksController *c) : wnd(w), contr(c) {
	QWidget *wgt = new QWidget;
	auto *v = new QVBoxLayout;
	auto *l = new QFormLayout;

	name = new QLineEdit;
	QLabel *label = new QLabel(tr("Add new tab: "));
	QPushButton *submit = new QPushButton(tr("Create"));
	submit->setProperty("newLineButton", "true");


	l->addRow(label);
	l->addRow(tr("Name: "), name);
	l->addRow(submit);

	l->setAlignment(label, Qt::AlignHCenter);
	v->setAlignment(Qt::AlignCenter);

	wgt->setLayout(l);
	wgt->setMinimumSize(250, 150);
	wgt->setMaximumSize(650, 150);
	v->addWidget(wgt);

	connect(name, &QLineEdit::returnPressed, this, &MNewGr::addClick);
	connect(submit, &QPushButton::clicked, this, &MNewGr::addClick);

	setLayout(v);
}

void MNewGr::addClick() {
	if (name->text() == "") return;
	QJsonObject o = {
			{"name", name->text()}
	};

	QTabWidget *tabs = wnd->tabs;
	contr->addNewTab(tabs->count() - 2, o);
	tabs->setCurrentIndex(tabs->count() - 3);
}