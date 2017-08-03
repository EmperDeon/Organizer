TEMPLATE = app
TARGET   = Organizer

QT += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

SOURCES += main.cpp \
mio.cpp \
mwgt.cpp \
editors/MEditorsController.cpp \
editors/MNewEd.cpp \
editors/MEdTab.cpp \
editors/MLsTab.cpp \
links/MLinksController.cpp \
links/MLink.cpp \
links/MGroup.cpp \
links/MNewGr.cpp

HEADERS += mio.h \
mwgt.h \
editors/MEditorsController.h \
editors/MNewEd.h \
editors/MEdTab.h \
editors/MLsTab.h \
links/MLinksController.h \
links/MLink.h \
links/MGroup.h \
links/MNewGr.h

RC_FILE = res.rc
RESOURCES += res.qrc
