/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_USROLLAREA_H
#define ORGANIZER_USROLLAREA_H

#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QScrollArea>


class UScrollArea : public QScrollArea {

public:
    explicit UScrollArea(QBoxLayout *l);
};


#endif //ORGANIZER_USROLLAREA_H
