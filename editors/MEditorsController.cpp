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

void MEditorsController::addNewTab(int i, const QJsonObject &o) {
	QString name = o["name"].toString("Error");
	MTab *w;

	switch (o["type"].toInt(-1)) {
		case 0:
			w = new MEdTab(o);
			break;
		case 1:
			w = new MLsTab(o);
			break;

		default:
			w = nullptr;
			break;
	}

	if (w != nullptr) {
		wnd->tabs->insertTab(i, w, name);
		tabs << w;
	}
}

MTab *MEditorsController::addNew() {
	return new MNewEd(wnd, this);
}

void MEditorsController::save() {
	QJsonObject obj;

	for (MTab *t : tabs) {
		if (t != nullptr)
			obj[t->getName()] = t->save();
	}

	Storage::getInstance()->saveDocument("documents", obj);
}

void MEditorsController::tabDel(QString name) {
	cont->remove(name);
}
