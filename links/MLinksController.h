#ifndef ORGANIZER_MLINKS_H
#define ORGANIZER_MLINKS_H

#include <mwgt.h>

class MWindow;

class MTabController;


class MLinksController : public MTabsController {
	MWindow *wnd;

public:
	SDocument *cont;

	explicit MLinksController(MWindow *w);

	void load() override;

	void save() override;

	MTab *addNew() override;

	void tabDel(QString name) override;

	~MLinksController() override = default;

	void addNewTab(int i, const QJsonObject &o) const;
};


#endif //ORGANIZER_MLINKS_H
