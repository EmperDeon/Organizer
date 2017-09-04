#ifndef ORGANIZER_NSYNC_H
#define ORGANIZER_NSYNC_H

#include <editors/MTabsController.h>

class MTabsController;


class NSync : public QObject {
    MTabsController *contr;
    QTimer *timer;

public:
    explicit NSync(MTabsController *c);

    void tryLoad();
};


#endif //ORGANIZER_NSYNC_H
