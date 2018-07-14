/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_WFILES_H
#define ORGANIZER_WFILES_H

#include <QtWidgets/QWidget>
#include <plugins/tabs/PTabFiles.h>
#include <utils/UScrollArea.h>
#include <plugins/tabs/PTabFile.h>

class PTabFiles;


class WFiles : public QWidget {
    PTabFiles *files;

    QVBoxLayout *list_l;
    UScrollArea *scroll;

public:
    explicit WFiles(PTabFiles *s_f);

    void updateFileList();

    void addFile();

    void delFile(const PTabFile &f);

    void saveFile(const PTabFile &f);

    void editFile(const PTabFile &f);
};


#endif //ORGANIZER_WFILES_H
