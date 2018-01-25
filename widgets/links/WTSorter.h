/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_WLSORTER_H
#define ORGANIZER_WLSORTER_H

#include <QtWidgets/QWidget>
#include <utils/widgets/UTreeWidget.h>


// Widget for sorting Links in linkGroups
class WTSorter : public QWidget {
    UTreeWidget *tree;

public:
    WTSorter();

    // Loads information about LinkGroups to QTreeWidget
    void reload();

    // Calls close
    void save();

protected:
    // Saves information about LinkGroups back to Storage
    void closeEvent(QCloseEvent *event) override;
};


#endif //ORGANIZER_WLSORTER_H
