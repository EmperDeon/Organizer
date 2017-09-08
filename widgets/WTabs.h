#ifndef ORGANIZER_WTABWIDGET_H
#define ORGANIZER_WTABWIDGET_H

#include <QtWidgets/QTabWidget>
#include <editors/MTab.h>
#include <editors/MTabsController.h>

class WMain;

class MTabsController;

class WTabs : public QTabWidget {
    WMain *main;
    MTabsController *contr;

    MTab *lastTab = nullptr, *newTab = nullptr;

    QList<MTab *> tabs;

    // Groups cycle variables
    QAction *action = nullptr;
    MTab::TabGroup current_group = MTab::All;
    QMap<QString, MTab::TabGroup> tab_groups;

public:
    explicit WTabs(WMain *m);

    int insertNewTab(int index, MTab *widget, const QString &string);

    void tabNew();

    void tabClose();

    void tabChange(int i);

    MTab *getTab(int i) { return dynamic_cast<MTab *>(widget(i)); }

    MTab *getCurrentTab() { return dynamic_cast<MTab *>(currentWidget()); }

    void cycleGroup();

    void groupBy(MTab::TabGroup gr = MTab::Editors);

    void setAction(QAction *act);

    QString findGroupName(MTab::TabGroup gr);

    QString findGroupAfter(QString name);
};


#endif //ORGANIZER_WTABWIDGET_H
