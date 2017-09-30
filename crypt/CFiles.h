#ifndef ORGANIZER_CFILES_H
#define ORGANIZER_CFILES_H


#include <QtCore/QString>

class CFiles {
    enum Type {
        Encrypt,
        Decrypt
    };

public:
    static void copyToEncryptedStorage(const QString &path, const QString &file);

    static void copyFromEncryptedStorage(const QString &path, const QString &file, const QString &save_path);

    static QByteArray process(Type type, const QByteArray &data);
};


#endif //ORGANIZER_CFILES_H
