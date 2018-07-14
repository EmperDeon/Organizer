/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_NSYNC_H
#define ORGANIZER_NSYNC_H

#include <tabs/TabsController.h>

class TabsController;


class NSync : public QObject {
    TabsController *contr;
    QTimer *timer;

public:
    explicit NSync(TabsController *c);

    void tryLoad();
};


#endif //ORGANIZER_NSYNC_H
