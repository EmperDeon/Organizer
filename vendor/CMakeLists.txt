cmake_minimum_required(VERSION 3.0)
project(Vendor)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost REQUIRED COMPONENTS regex)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(vendor/verdigris/src)
add_subdirectory(simple_ossl)


SET(M_S cpp-markdown/src/markdown.cpp cpp-markdown/src/markdown-tokens.cpp)
SET(M_H cpp-markdown/src/markdown.h cpp-markdown/src/markdown-tokens.h)

add_library(cpp-markdown ${M_S} ${M_H})
target_link_libraries(cpp-markdown ${Boost_LIBRARIES})
