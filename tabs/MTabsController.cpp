#include <tabs/files/MFlGroup.h>
#include "tabs/editors/MEdTab.h"
#include "tabs/links/MGroup.h"
#include "tabs/lists/MLsTab.h"
#include "tabs/MTabsController.h"

MTabsController::MTabsController(WMain *w) : wnd(w) {
    sync = new NSync(this);
}

void MTabsController::load() {
    QJsonArray docs = Storage::getInstance()->getDocs();

    int i = 0;
    for (const auto &o : docs) {
        QJsonObject ob = o.toObject();
        QString name = ob["name"].toString("Error");

        if (tabs.contains(name)) {
            tabs[name]->load(ob);

        } else {
            addNewTab(name, ob, i);
        }
    }
}

void MTabsController::addNewTab(const QString &name, const QJsonObject &o, int i) {
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
        case MTab::FilesGroup:
            w = new MFlGroup(o);
            break;

        default:
            w = nullptr;
            break;
    }

    if (w != nullptr) {
//        wnd->tabs->insertNewTab(i, w, name);
        wnd->tabs->addTab(w, name);
        tabs[name] = w;
    }
}

void MTabsController::save() {
    QJsonArray obj;

    for (MTab *t : tabs.values()) {
        if (t != nullptr)
            obj << t->save();
    }

    Storage::getInstance()->setDocs(obj);
}

void MTabsController::tabDel(QString name) {// Fixme
//	cont->remove(name);
}

QList<MTab *> MTabsController::selectByGroup(MTab::TabGroup gr) {
    auto r = QList<MTab *>();

    for (const auto &n : tabs.keys()) {
        if (tabs[n]->isInGroup(gr)) {
            r << tabs[n];
        }
    }

    return r;
}
