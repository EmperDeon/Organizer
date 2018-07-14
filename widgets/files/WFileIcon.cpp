/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "WFileIcon.h"

WFileIcon::WFileIcon(const QString &type) : QLabel() {
    setPixmap(getIcon(type));
    setFixedSize(24, 24);
}

QPixmap WFileIcon::getIcon(const QString &type) {
    QString icon;

    icon = "none";
    Q_UNUSED(type);

    return QPixmap(":/icons/file-types/" + icon + ".png").scaledToWidth(24, Qt::SmoothTransformation);
}
