/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_USINGLETON_H
#define ORGANIZER_USINGLETON_H

template<class T>
class USingleton {
public:
    static T *getInstance() {
        static T *instance = nullptr;

        if (instance == nullptr) {
            instance = new T;
        }

        return instance;
    }
};

#endif //ORGANIZER_USINGLETON_H
