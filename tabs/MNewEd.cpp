#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "MNewEd.h"

MNewEd::MNewEd(WMain *w, MTabsController *c) : wnd(w), contr(c) {
	QWidget *wgt = new QWidget;
	auto *v = new QVBoxLayout;
	auto *l = new QFormLayout;

	name = new QLineEdit;
	type = new QComboBox;
	QLabel *label = new QLabel(tr("Add new tab: "));
	QPushButton *submit = new QPushButton(tr("Create"));
	submit->setProperty("newLineButton", "true");

    type->addItem("Plain text", MTab::Text);
    type->addItem("List", MTab::List);
    type->addItem("Links group", MTab::LinksGroup);

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
	QJsonObject o = {
            {"name", name->text()},
            {"type", type->currentData().toInt()}
	};

	QTabWidget *tabs = wnd->tabs;
    contr->addNewTab(name->text(), o, tabs->count() - 2);
	tabs->setCurrentIndex(tabs->count() - 3);
}
