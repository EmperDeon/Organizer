/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_MNEWED_H
#define ORGANIZER_MNEWED_H

#include <widgets/WMain.h>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include "MTabsController.h"

class WMain;

class MTabsController;

class MNewTab : public MTab {
    WMain *wnd;
    MTabsController *contr;

    QComboBox *type;
    QLineEdit *name;

public:
    MNewTab(WMain *w, MTabsController *c);

    void addClick();

    friend class WMain;
};

#endif //ORGANIZER_MNEWED_H
