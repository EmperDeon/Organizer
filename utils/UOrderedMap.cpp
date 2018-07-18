/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "UOrderedMap.h"
#include "Utils.h"

template<class Key, class T>
UOrderedMap<Key, T>::UOrderedMap(const UOrderedMap<Key, T> &other) {
    m_vals = other.m_vals;
    m_keys = other.m_keys;
}

template<class K, class V>
void UOrderedMap<K, V>::addItems(const QMap<K, V> &obj, UOrderedMap::Comparator comp) {
    for (const K &k : obj.keys()) {
        m_vals[k] = obj[k];
        m_keys << k;
    }

    sort_by(m_keys, ([this, comp](const K &k1, const K &k2) {
        return comp(m_vals[k1], m_vals[k2]);
    }));
}

template<class K, class V>
QList<K> UOrderedMap<K, V>::keys() {
    return m_keys;
}

template<class Key, class T>
int UOrderedMap<Key, T>::size() const {
    return m_keys.size();
}

template<class Key, class T>
bool UOrderedMap<Key, T>::isEmpty() const {
    return m_keys.size() == 0;
}

template<class Key, class T>
int UOrderedMap<Key, T>::remove(const Key &key) {
    m_keys.removeAll(key);
    return m_vals.remove(key);
}

template<class Key, class T>
T UOrderedMap<Key, T>::take(const Key &key) {
    m_keys.removeAll(key);
    return m_vals.take(key);
}

template<class Key, class T>
bool UOrderedMap<Key, T>::contains(const Key &key) const {
    return m_keys.contains(key);
}

template<class Key, class T>
const Key UOrderedMap<Key, T>::key(const T &value, const Key &defaultKey) const {
    Key k;
    if ((k = m_vals.key(value) != defaultKey)) {
        return k;
    } else {
        return defaultKey;
    }
}

template<class Key, class T>
const T UOrderedMap<Key, T>::value(const Key &key, const T &defaultValue) const {
    if (contains(key)) {
        return m_vals[key];
    } else {
        return defaultValue;
    }
}

template<class Key, class T>
T &UOrderedMap<Key, T>::operator[](const Key &key) {
    return m_vals[key];
}

template<class Key, class T>
const T UOrderedMap<Key, T>::operator[](const Key &key) const {
    return m_vals[key];
}

template<class Key, class T>
void UOrderedMap<Key, T>::insert(const Key &key, const T &value) {
    m_keys.append(key);
    m_vals.insert(key, value);
}
