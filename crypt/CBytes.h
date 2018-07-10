/*
	Copyright (c) 2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_CBYTES_H
#define ORGANIZER_CBYTES_H

#include <QtCore/QByteArray>
#include <QtCore/QString>

#define bytes_data(var) (var).data(), (var).size()
#define bytes_dataI(var) (var).data(), (var).sizeI()


class CBytes {
    QByteArray b_array;

public:
    CBytes();

    CBytes(const QString &base);

    CBytes(const CBytes &arr);

    CBytes(const QByteArray &arr);

    CBytes(const char *arr, int size = -1);

    CBytes(int size, char c);

    unsigned char *data();

    const unsigned char *data() const;

    unsigned char back();

    QString toHex();

    QString toBase();

    int sizeI() const;

    unsigned long size() const;

    QByteArray array() const;

    CBytes mid(int index, int len = -1) const;

    void append(int len, char c);

    void remove(int index, int len);

    CBytes &operator+=(const CBytes &a);


    static CBytes fromHex(const QString &hex);

    static CBytes fromBase(const QString &base);
};

inline const CBytes operator+(const CBytes &a1, const CBytes &a2) { return CBytes(a1) += a2; }


#endif //ORGANIZER_CBYTES_H
