/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_TABNEW_H
#define ORGANIZER_TABNEW_H

#include <widgets/WMain.h>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include "TabsController.h"

class WMain;

class TabsController;


class TabNew : public Tab {
    WMain *wnd;
    TabsController *contr;

    QComboBox *type;
    QLineEdit *name;

public:
    TabNew(WMain *w, TabsController *c);

    void addClick();

    friend class WMain;
};

#endif //ORGANIZER_TABNEW_H
