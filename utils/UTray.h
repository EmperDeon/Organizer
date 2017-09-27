#ifndef ORGANIZER_UTRAY_H
#define ORGANIZER_UTRAY_H

#include <QtWidgets/QSystemTrayIcon>
#include <QtWidgets/QMainWindow>

class UTray : public QSystemTrayIcon {
    QMainWindow *wnd;

    void trayClick(QSystemTrayIcon::ActivationReason reason);

    void trayToggle();

public:
    explicit UTray(QMainWindow *w);
};


#endif //ORGANIZER_UTRAY_H
