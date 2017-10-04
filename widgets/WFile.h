#ifndef ORGANIZER_WFILE_H
#define ORGANIZER_WFILE_H

#include <storage/SFile.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>


class WFile : public QWidget {
public:
    explicit WFile(const SFile &f);


    QPushButton *createButton(const QString &icon, const QString &tooltip) const;
};


#endif //ORGANIZER_WFILE_H
