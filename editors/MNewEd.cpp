#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "MNewEd.h"

// MNewTab
MNewEd::MNewEd(MWindow *w, MEditorsController *c) : wnd(w), contr(c) {
	QWidget *wgt = new QWidget;
	auto *v = new QVBoxLayout;
	auto *l = new QFormLayout;

	name = new QLineEdit;
	type = new QComboBox;
	QLabel *label = new QLabel(tr("Add new tab: "));
	QPushButton *submit = new QPushButton(tr("Create"));
	submit->setProperty("newLineButton", "true");

	type->addItems({"Plain Text", "List"});

	l->addRow(label);
	l->addRow(tr("Name: "), name);
	l->addRow(tr("Type: "), type);
	l->addRow(submit);

	l->setAlignment(label, Qt::AlignHCenter);
	v->setAlignment(Qt::AlignCenter);

	wgt->setLayout(l);
	wgt->setMinimumSize(250, 150);
	wgt->setMaximumSize(650, 150);
	v->addWidget(wgt);

	connect(submit, &QPushButton::clicked, this, &MNewEd::addClick);

	setLayout(v);
}

void MNewEd::addClick() {
	if (name->text() == "") return;
	QJsonObject o;
	o["name"] = name->text();
	o["type"] = type->currentIndex();

	contr->cont->insert(name->text(), o);

	QTabWidget *tabs = wnd->tabs;
	contr->addNewTab(tabs->count() - 2, o);
	tabs->setCurrentIndex(tabs->count() - 3);
}
// MNewTab
