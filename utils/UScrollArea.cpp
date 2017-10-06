/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "UScrollArea.h"

UScrollArea::UScrollArea(QBoxLayout *l) {
    auto *w = new QWidget;

    w->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    w->setLayout(l);

    setWidget(w);
    setWidgetResizable(true);
    setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
}
