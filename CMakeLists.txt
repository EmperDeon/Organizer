cmake_minimum_required(VERSION 3.3)
project(Organizer)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets)
find_package(Qt5Network)
find_package(Qca-qt5)


set(CMAKE_CXX_FLAGS "-std=c++14")
# -fPIC ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}


SET(M_S
        main.cpp
        mwgt.cpp

        res.rc

        crypt/CAes.cpp
        crypt/CRsa.cpp
        crypt/CTools.cpp

        editors/MEditorsController.cpp
        editors/MNewEd.cpp
        editors/MEdTab.cpp
        editors/MLsTab.cpp

        links/MLinksController.cpp
        links/MLink.cpp
        links/MGroup.cpp
        links/MNewGr.cpp

        network/NAuth.cpp
        network/NCrypt.cpp
        network/Network.cpp

        storage/Storage.cpp
        storage/SSecure.cpp
        storage/SDocument.cpp

        utils/UPassDialog.cpp
        )


SET(M_H
        mwgt.h
        vars.h

        crypt/CAes.h
        crypt/CRsa.h
        crypt/CTools.h

        editors/MEditorsController.h
        editors/MNewEd.h
        editors/MEdTab.h
        editors/MLsTab.h

        links/MLinksController.h
        links/MLink.h
        links/MGroup.h
        links/MNewGr.h

        network/NAuth.h
        network/NCrypt.h
        network/Network.h

        storage/Storage.h
        storage/SSecure.h
        storage/SDocument.h

        utils/UPassDialog.h
        )

qt5_wrap_cpp(GENERATED_SOURCES ${M_H})
qt5_add_resources(UI_RESOURCES res.qrc)

add_executable(Organizer ${M_S} ${M_H} ${UI_RESOURCES})
qt5_use_modules(Organizer Core Widgets Network)

target_link_libraries(Organizer ${Qt5Core_QTMAIN_LIBRARIES} qca-qt5)
