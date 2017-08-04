#ifndef ORGANIZER_MWGT_H
#define ORGANIZER_MWGT_H

#include <storage/Storage.h>
#include <mtab.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSystemTrayIcon>
#include <QtCore/QDateTime>
#include <QtCore/QTimer>

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
Q_OBJECT

	MTabsController *contr = nullptr;
	QAction *chAction;

	QSystemTrayIcon *tray;
	QMenu *mfile;

	MTab *lastTab = nullptr, *newTab = nullptr;

public:
	QTabWidget *tabs;

	MTab *getTab(int i) { return dynamic_cast<MTab *>(tabs->widget(i)); }

	MTab *getCurrentTab() { return dynamic_cast<MTab *>(tabs->currentWidget()); }

//public slots:
	void tabNew();

	void tabClose();

	void tabChange(int i);

	void importFrom();

	void exportTo();

	void trayClick(QSystemTrayIcon::ActivationReason reason);

	void trayToggle();

	void updateMenu();

	void enableSync();

	void newRegister();

protected:
	void closeEvent(QCloseEvent *e) override;

	void hideEvent(QHideEvent *e) override;

public:
	MWindow();

	void constructMenuBar();

	void changeWidget();

};

#endif //ORGANIZER_MWGT_H
