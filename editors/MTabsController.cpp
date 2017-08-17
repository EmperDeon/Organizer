#include <editors/MTabsController.h>
#include <links/MGroup.h>
#include "MEdTab.h"
#include "MLsTab.h"
#include "MNewEd.h"


MTabsController::MTabsController(MWindow *w) : wnd(w) {
	cont = Storage::getInstance()->getDocument("documents");
}

void MTabsController::load() {
	int i = 0;
    for (const QJsonValue &o : *cont)
        addNewTab(i, o.toObject());
}

void MTabsController::addNewTab(int i, const QJsonObject &o) {
	QString name = o["name"].toString("Error");
	MTab *w;

    MTab::TabType type = static_cast<MTab::TabType>(o["type"].toInt(100));

    switch (type) {
        case MTab::Text:
            w = new MEdTab(o);
            break;
        case MTab::List:
            w = new MLsTab(o);
            break;
        case MTab::LinksGroup:
            w = new MGroup(o);
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

MTab *MTabsController::addNew() {
	return new MNewEd(wnd, this);
}

void MTabsController::save() {
    QJsonArray obj;

	for (MTab *t : tabs) {
		if (t != nullptr)
            obj << t->save();
    }

    Storage::getInstance()->saveDocument(obj);
}

void MTabsController::tabDel(QString name) {
//	cont->remove(name);
}
