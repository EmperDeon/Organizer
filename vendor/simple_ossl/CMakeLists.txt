cmake_minimum_required(VERSION 3.1.0)
project(simple-ossl)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenSSL REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)

message(STATUS "OpenSSL version: " ${OPENSSL_VERSION})

SET(SOURCES Aes.cpp Hash.cpp Rsa.cpp Utils.cpp simple_ossl.cpp)
SET(HEADERS include/Aes.h include/Hash.h include/Rsa.h include/Utils.h include/simple_ossl.h)

add_library(simple-ossl ${SOURCES} ${HEADERS})
target_link_libraries(simple-ossl Qt5::Core ${OPENSSL_LIBRARIES})
