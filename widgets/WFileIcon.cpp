#include "WFileIcon.h"

WFileIcon::WFileIcon(const QString &type) : QLabel() {
    setPixmap(getIcon(type));
    setFixedSize(24, 24);
}

QPixmap WFileIcon::getIcon(const QString &type) {
    QString icon;

    icon = "none";

    return QPixmap(":/icons/file-types/" + icon + ".png").scaledToWidth(24, Qt::SmoothTransformation);
}
