#ifndef ORGANIZER_WFILES_H
#define ORGANIZER_WFILES_H


#include <QtWidgets/QWidget>
#include <storage/SFiles.h>
#include <utils/UScrollArea.h>

class WFiles : public QWidget {
    SFiles *files;

    QVBoxLayout *list_l;
    UScrollArea *scroll;

public:
    explicit WFiles(const QString &name);

    explicit WFiles(SFiles *s_f);

    void updateFileList();
};


#endif //ORGANIZER_WFILES_H
