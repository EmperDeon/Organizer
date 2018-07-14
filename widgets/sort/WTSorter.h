/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_WLSORTER_H
#define ORGANIZER_WLSORTER_H

#include <QtWidgets/QDialog>
#include <utils/widgets/UTreeWidget.h>


// Widget for sorting tabs
class WTSorter : public QDialog {
    UTreeWidget *tree;

public:
    WTSorter();

    // Loads information about LinkGroups to QTreeWidget
    void reload();

    // Opens dialog
    static void sortTabs();

protected:
    // Saves information about LinkGroups back to Storage
    QJsonArray toDocs();
};


#endif //ORGANIZER_WLSORTER_H
