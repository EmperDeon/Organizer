TEMPLATE = lib
TARGET = markdown

CONFIG += c++14 staticlib

SOURCES += cpp-markdown/src/markdown.cpp cpp-markdown/src/markdown-tokens.cpp
HEADERS += cpp-markdown/src/markdown.h cpp-markdown/src/markdown-tokens.cpp
