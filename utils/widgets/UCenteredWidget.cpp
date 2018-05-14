/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "UCenteredWidget.h"

UCenteredWidget::UCenteredWidget(int w, int h) {
    auto *l = new QVBoxLayout;
    wgt = new QWidget;

    wgt->setMaximumSize(w, h);

    l->addWidget(wgt, 0, Qt::AlignCenter);

    setLayout(l);
}

void UCenteredWidget::setBoxLayout(QBoxLayout *layout) {
    wgt->setLayout(layout);
}
