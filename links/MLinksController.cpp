#include "links/MLinksController.h"
#include "MGroup.h"
#include "MNewGr.h"

MLinksController::MLinksController(MWindow *w) : wnd(w), cont(Storage::getInstance()->getDocument("links")) {

}

void MLinksController::load() {
	for (const QJsonObject &o : cont->getDocs()) {
		addNewTab(wnd->tabs->count() - 2, o);
	}
}

void MLinksController::save() {
	for (int i = 0; i < wnd->tabs->count(); i++) {
		MTab *t = wnd->getTab(i);
		if (t != nullptr)
			t->save();
	}

	Storage::getInstance()->saveDocument("links", *cont);
	Storage::getInstance()->saveJson();
}

MTab *MLinksController::addNew() {
	return new MNewGr(wnd, this);
}

void MLinksController::addNewTab(int i, const QJsonObject &o) const {
	QString name = o["name"].toString("Error");

	MTab *w = new MGroup(cont, o);
	wnd->tabs->insertTab(i, w, name);
}

void MLinksController::tabDel(QString name) {
	cont->remove(name);
}
