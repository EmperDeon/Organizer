#include <QtWidgets/QVBoxLayout>
#include "MEdTab.h"

// MEdTab
MEdTab::MEdTab(SDocument *c, QJsonObject o) : cont(c), obj(o), name(o["name"].toString()) {
	auto *l = new QVBoxLayout;
	edit = new QPlainTextEdit;

	edit->setPlainText(o["text"].toString());

	connect(edit, &QPlainTextEdit::textChanged, this, &MTab::updated);

	l->addWidget(edit);
	setLayout(l);
}

QString MEdTab::getDesc() {
	return "Plain text: " + name;
}

void MEdTab::save() {
	obj["text"] = edit->toPlainText();

	cont->insert(name, obj);
}

void MEdTab::importFrom(QString s) {
	edit->setPlainText(edit->toPlainText() + "\n" + s);
}

QString MEdTab::exportTo() {
	return edit->toPlainText();
}
// MEdTab