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
