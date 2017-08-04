#include "links/MLinksController.h"
#include "MGroup.h"
#include "MNewGr.h"
#include <QDebug>

MLinksController::MLinksController(MWindow *w) : wnd(w), cont(Storage::getInstance()->getDocument("links")) {

}

void MLinksController::load() {
	for (const QJsonObject &o : cont->getDocs()) {
		addNewTab(wnd->tabs->count() - 2, o);
	}
}

void MLinksController::save() {
	QJsonObject obj;

	for (MTab *t : tabs) {
		if (t != nullptr) {
			obj[t->getName()] = t->save();
		}
	}

	Storage::getInstance()->saveDocument("links", obj);
	Storage::getInstance()->saveJson();
}

MTab *MLinksController::addNew() {
	return new MNewGr(wnd, this);
}

void MLinksController::addNewTab(int i, const QJsonObject &o) {
	QString name = o["name"].toString("Error");

	auto *w = new MGroup(o);
	tabs << w;
	wnd->tabs->insertTab(i, w, name);
}

void MLinksController::tabDel(QString name) {
	cont->remove(name);
}
