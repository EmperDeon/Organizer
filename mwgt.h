#ifndef ORGANIZER_MWGT_H
#define ORGANIZER_MWGT_H

#include <storage/Storage.h>
#include <mtab.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSystemTrayIcon>
#include <QtCore/QDateTime>
#include <QtCore/QTimer>
#include <widgets/WSync.h>

class Storage;

class MTab;


class MTabsController {
public:
	virtual void load() = 0;

	virtual void save() = 0;

	virtual MTab *addNew() = 0;

	virtual void tabDel(QString name) = 0;

	virtual ~MTabsController() = default;
};

class MWindow : public QMainWindow {
	MTabsController *contr = nullptr;
	QAction *chAction;

	QSystemTrayIcon *tray;
	WSync *wsync;

	MTab *lastTab = nullptr, *newTab = nullptr;


	MTab *getTab(int i) { return dynamic_cast<MTab *>(tabs->widget(i)); }

	MTab *getCurrentTab() { return dynamic_cast<MTab *>(tabs->currentWidget()); }

public:
	QTabWidget *tabs;

	void tabNew();

	void tabClose();

	void tabChange(int i);

	void importFrom();

	void exportTo();

	void trayClick(QSystemTrayIcon::ActivationReason reason);

	void trayToggle();

protected:
	void closeEvent(QCloseEvent *e) override;

	void hideEvent(QHideEvent *e) override;

public:
	MWindow();

	void constructMenuBar();

	void changeWidget();

	// Singleton
	static MWindow *getInstance() {
		static MWindow *instance = nullptr;

		if (instance == nullptr) {
			instance = new MWindow;
		}

		return instance;
	}

	void saveController() { contr->save(); }
};

#endif //ORGANIZER_MWGT_H
