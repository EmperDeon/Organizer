/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_UCENTEREDWIDGET_H
#define ORGANIZER_UCENTEREDWIDGET_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QBoxLayout>


class UCenteredWidget : public QWidget {
    QWidget *wgt = nullptr;

public:
    UCenteredWidget(int w, int h);

    void setBoxLayout(QBoxLayout *layout);
};


#endif //ORGANIZER_UCENTEREDWIDGET_H
