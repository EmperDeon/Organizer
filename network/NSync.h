/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_NSYNC_H
#define ORGANIZER_NSYNC_H

#include <tabs/MTabsController.h>

class MTabsController;


class NSync : public QObject {
    MTabsController *contr;
    QTimer *timer;

public:
    explicit NSync(MTabsController *c);

    void tryLoad();
};


#endif //ORGANIZER_NSYNC_H
