#ifndef ORGANIZER_WFILEICON_H
#define ORGANIZER_WFILEICON_H

#include <QtWidgets/QLabel>


class WFileIcon : public QLabel {
public:
    explicit WFileIcon(const QString &type);

    QPixmap getIcon(const QString &type);
};


#endif //ORGANIZER_WFILEICON_H
