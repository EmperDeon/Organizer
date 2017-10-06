#ifndef ORGANIZER_WFILE_H
#define ORGANIZER_WFILE_H

#include <plugins/tabs/PTabFile.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>


class WFile : public QWidget {
Q_OBJECT

    PTabFile file;

    // Slots
    void int_save();

    void int_edit();

    void int_del();

signals:

    void save(const PTabFile &f);

    void edit(const PTabFile &f);

    void del(const PTabFile &f);

public:
    explicit WFile(const PTabFile &f);


    QPushButton *createButton(const QString &icon, const QString &tooltip) const;
};


#endif //ORGANIZER_WFILE_H
