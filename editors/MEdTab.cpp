#include <QtWidgets/QVBoxLayout>
#include "MEdTab.h"

// MEdTab
MEdTab::MEdTab(const QJsonObject &o) : MTab(o), name(o["name"].toString()) {
	auto *l = new QVBoxLayout;
	edit = new QPlainTextEdit;

	connect(edit, &QPlainTextEdit::textChanged, this, &MTab::updated);

	l->addWidget(edit);
	setLayout(l);

	load();
}

QString MEdTab::getDesc() {
	return "Plain text: " + name;
}

void MEdTab::importFrom(QString s) {
	edit->setPlainText(edit->toPlainText() + "\n" + s);
}

QString MEdTab::exportTo() {
	return edit->toPlainText();
}

void MEdTab::fromJson(QJsonValue v) {
	edit->setPlainText(v.toString());
}

QJsonValue MEdTab::toJson() {
	return edit->toPlainText();
}
// MEdTab