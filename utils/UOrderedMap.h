/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_UORDEREDMAP_H
#define ORGANIZER_UORDEREDMAP_H

#include <QtCore/QMap>
#include <QtCore/QString>
#include <vendor/additions.h>

/*
 * Add items with comparator and get Map with keys sorted by comparator
 * */
template<class Key, class T>
class UOrderedMap {
protected:
    QMap<Key, T> m_vals;
    QList<Key> m_keys;

public:
    UOrderedMap() = default;

    UOrderedMap(const UOrderedMap<Key, T> &other);

    typedef std::function<bool(const T &, const T &)> Comparator;

    // Own
    void addItems(const QMap<Key, T> &obj, Comparator comp);


    // STL
    typedef typename QList<Key>::iterator iterator;
    typedef typename QList<Key>::const_iterator const_iterator;

    iterator begin() { return m_keys.begin(); }

    const_iterator begin() const { return m_keys.begin(); }

    const_iterator cbegin() const { return m_keys.cbegin(); }

    iterator end() { return m_keys.end(); }

    const_iterator end() const { return m_keys.end(); }

    const_iterator cend() const { return m_keys.cend(); }

    // Qt
    QList<Key> keys();

    QList<T> values();

    int size() const;

    void clear();

    bool isEmpty() const;

    int remove(const Key &key);

    T take(const Key &key);

    bool contains(const Key &key) const;

    const Key key(const T &value, const Key &defaultKey = Key()) const;

    const T value(const Key &key, const T &defaultValue = T()) const;

    T &operator[](const Key &key);

    const T operator[](const Key &key) const;

    void insert(const Key &key, const T &value);

    void insertAfter(const Key &after, const Key &key, const T &value);

    void swap(const Key &key1, const Key &key2);
};


#endif //ORGANIZER_UORDEREDMAP_H
