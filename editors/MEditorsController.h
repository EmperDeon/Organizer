#ifndef ORGANIZER_MEDITORS_H
#define ORGANIZER_MEDITORS_H

#include <storage/Storage.h>
#include <mwgt.h>

class MWindow;

class Storage;

class MTab;

class MTabController;

class MEditorsController : public MTabsController {
	MWindow *wnd;

public:
	SDocument *cont;

	explicit MEditorsController(MWindow *w);

	void load() override;

	void save() override;

	MTab *addNew() override;

	void tabDel(QString name) override;

	~MEditorsController() override = default;

	void addNewTab(int i, const QJsonObject &o) const;
};


#endif //ORGANIZER_MEDITORS_H
