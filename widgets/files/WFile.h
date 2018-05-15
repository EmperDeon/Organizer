/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_WFILE_H
#define ORGANIZER_WFILE_H

#include <plugins/tabs/PTabFile.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <vendor/verdigris/src/wobjectdefs.h>

W_REGISTER_ARGTYPE(PTabFile)
W_REGISTER_ARGTYPE(PTabFile*)

class WFile : public QWidget {
    W_OBJECT(WFile);

    PTabFile file;

    // Slots
    void int_save();

    void int_edit();

    void int_del();

public /* signals */:

    void save(const PTabFile &f) W_SIGNAL(save, f)

    void edit(const PTabFile &f) W_SIGNAL(edit, f)

    void del(const PTabFile &f) W_SIGNAL(del, f)

public:
    explicit WFile(const PTabFile &f);

    QPushButton *createButton(const QString &icon, const QString &tooltip) const;
};

#endif //ORGANIZER_WFILE_H
