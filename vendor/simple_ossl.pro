TEMPLATE = lib
TARGET = simple_ossl

QT += core

CONFIG += c++14 staticlib

SOURCES += simple_ossl/Aes.cpp \
 simple_ossl/Hash.cpp \
 simple_ossl/Rsa.cpp \
 simple_ossl/Utils.cpp \
 simple_ossl/simple_ossl.cpp

HEADERS += simple_ossl/include/Aes.h \
 simple_ossl/include/Hash.h \
 simple_ossl/include/Rsa.h \
 simple_ossl/include/Utils.h \
 simple_ossl/include/simple_ossl.h

INCLUDEPATH += $$PWD/simple_ossl
