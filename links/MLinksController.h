#ifndef ORGANIZER_MLINKS_H
#define ORGANIZER_MLINKS_H

#include <mwgt.h>

class MWindow;

class MTabController;


class MLinksController : public MTabsController {
	MWindow *wnd;
	QList<MTab *> tabs;

public:
	SDocument *cont;

	explicit MLinksController(MWindow *w);

	void load() override;

	void save() override;

	MTab *addNew() override;

	void tabDel(QString name) override;

	~MLinksController() override = default;

	void addNewTab(int i, const QJsonObject &o);
};


#endif //ORGANIZER_MLINKS_H
