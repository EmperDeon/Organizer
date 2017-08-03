#include <editors/MEditorsController.h>
#include "MEdTab.h"
#include "MLsTab.h"
#include "MNewEd.h"


MEditorsController::MEditorsController(MWindow *w) : wnd(w) {
	cont = Storage::getInstance()->getDocument("documents");
}

void MEditorsController::load() {
	int i = 0;
	for (const QJsonObject &o : cont->getDocs())
		addNewTab(i, o);
}

void MEditorsController::addNewTab(int i, const QJsonObject &o) const {
	QString name = o["name"].toString("Error");
	MTab *w;

	switch (o["type"].toInt(-1)) {
		case 0:
			w = new MEdTab(cont, o);
			break;
		case 1:
			w = new MLsTab(cont, o);
			break;

		default:
			w = nullptr;
			break;
	}

	if (w != nullptr)
		wnd->tabs->insertTab(i, w, name);
}

MTab *MEditorsController::addNew() {
	return new MNewEd(wnd, this);
}

void MEditorsController::save() {
	for (int i = 0; i < wnd->tabs->count() - 1; i++) {
		MTab *t = wnd->getTab(i);
		if (t != nullptr) t->save();

	}

	Storage::getInstance()->saveDocument("documents", *cont);
	Storage::getInstance()->saveJson();
}

void MEditorsController::tabDel(QString name) {
	cont->remove(name);
}
