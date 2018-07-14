/*
	Copyright (c) 2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "CBytes.h"

CBytes::CBytes() = default;

CBytes::CBytes(const QString &base) : CBytes(CBytes::fromBase(base)) {}

CBytes::CBytes(const CBytes &arr) : b_array(arr.b_array) {}

CBytes::CBytes(const QByteArray &arr) : b_array(arr) {}

CBytes::CBytes(const char *arr, int size) : b_array(arr, size) {}

CBytes::CBytes(int size, char c) : b_array(size, c) {}

unsigned char *CBytes::data() {
    return reinterpret_cast<unsigned char *>(b_array.data());
}

const unsigned char *CBytes::data() const {
    return reinterpret_cast<const unsigned char *>(b_array.data());
}

unsigned char CBytes::back() {
    return static_cast<unsigned char>(b_array.at(sizeI() - 1));
}

QString CBytes::toHex() {
    return QString::fromUtf8(b_array.toHex());
}

QString CBytes::toBase() {
    return QString::fromUtf8(b_array.toBase64());
}

CBytes CBytes::fromHex(const QString &hex) {
    return QByteArray::fromHex(hex.toUtf8());
}

CBytes CBytes::fromBase(const QString &base) {
    return QByteArray::fromBase64(base.toUtf8());
}

int CBytes::sizeI() const {
    return b_array.size();
}

unsigned long CBytes::size() const {
    return (unsigned long) sizeI();
}

QByteArray CBytes::array() const {
    return b_array;
}

CBytes CBytes::mid(int index, int len) const {
    return b_array.mid(index, len);
}

void CBytes::append(int len, char c) {
    b_array.append(len, c);
}

void CBytes::remove(int index, int len) {
    b_array.remove(index, len);
}

CBytes &CBytes::operator+=(const CBytes &a) {
    b_array.append(a.b_array);
    return *this;
}

CBytes CBytes::left(unsigned long len) {
    return b_array.left((int) len);
}
