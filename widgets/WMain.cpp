#include "WMain.h"
#include <QtWidgets/QApplication>
#include <QtGui/QHideEvent>
#include <QtWidgets/QInputDialog>


// Constructor
WMain::WMain() {
    wsync = new WSync;
    contr = new MTabsController(this);
    tabs = new WTabs(this);

    constructMenuBar();

    qApp->setWindowIcon(QIcon(":/icon.ico"));

    // Create tray
    tray = new QSystemTrayIcon;
    tray->setIcon(QIcon(":/icon.ico"));
    tray->show();

    auto *trayMenu = new QMenu;

    QAction *trayClick = new QAction("Toggle state");
    connect(trayClick, &QAction::triggered, this, &WMain::trayToggle);

    trayMenu->addAction(trayClick);
    tray->setContextMenu(trayMenu);

    connect(tray, &QSystemTrayIcon::activated, this, &WMain::trayClick);
    // Create tray

    contr->load();
    tabs->setMovable(true);

    tabs->groupBy();


    setCentralWidget(tabs);
    setGeometry(100, 100, 750, 500);
}

void WMain::constructMenuBar() {
    QMenuBar *menu = this->menuBar();

    QMenu *mfile = new QMenu("File");
    mfile->addAction("Import", this, &WMain::importFrom);
    mfile->addAction("Export", this, &WMain::exportTo);
    mfile->addSeparator();
    mfile->addAction("Save", [=]() { contr->save(); }, QKeySequence::Save);
    mfile->addAction("Exit", this, &WMain::close, QKeySequence(Qt::CTRL + Qt::Key_Q));

    QMenu *mtabs = new QMenu("Tabs");
    mtabs->addAction("Add new tab", tabs, &WTabs::tabNew);
    mtabs->addAction("Delete tab", tabs, &WTabs::tabClose);

    QAction *chAction = new QAction("Editors");
    connect(chAction, &QAction::triggered, tabs, &WTabs::cycleGroup);
    tabs->setAction(chAction);

    QMenu *mhelp = new QMenu("Help");
    mhelp->addAction("About program");

    menu->addMenu(mfile);
    menu->addMenu(mtabs);
    menu->addAction(chAction);
    menu->addMenu(mhelp);
    menu->addMenu(wsync->getMenu());
}
// Constructor


// Menu Slots
void WMain::importFrom() {
    bool ok;
    QString s = QInputDialog::getMultiLineText(this, "Enter text", "Text: ", "", &ok);
    if (ok) tabs->getCurrentTab()->importFrom(s);
}

void WMain::exportTo() {
    QInputDialog::getMultiLineText(this, "Exported text", "Text: ", tabs->getCurrentTab()->exportTo());
}
// Menu Slots


// Widget events
void WMain::closeEvent(QCloseEvent *e) {
    Q_UNUSED(e)

    contr->save();
    Storage::getInstance()->saveJson();
    tray->hide();
}

void WMain::hideEvent(QHideEvent *e) {
    hide();

    Storage::getInstance()->saveJson();
    e->accept();
}

void WMain::trayClick(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger) {
        trayToggle();
    }
}

void WMain::trayToggle() {
    if (!isVisible()) {
        if (isMinimized()) showNormal();
        this->show();
        qApp->setActiveWindow(this);

    } else {
        this->hide();
    }
}
// Widget events


void WMain::changeWidget() {
////	Unload previous controller
//	if (contr != nullptr) {
//        saveController();
//		delete contr;
//
//        Storage::getInstance()->saveJson();
//	}
//
////	Construct and load new
//	contr = new MTabsController(this);
//
//
////	Clear Tabs
//	tabs->clear();
//	newTab = nullptr;
}