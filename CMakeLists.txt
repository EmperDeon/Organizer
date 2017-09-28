cmake_minimum_required(VERSION 3.0)
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
        res.rc

        crypt/CAes.cpp
        crypt/CRsa.cpp
        crypt/CTools.cpp

        tabs/editors/MEdTab.cpp

        tabs/links/MLink.cpp
        tabs/links/MGroup.cpp

        tabs/lists/MLsTab.cpp

        tabs/MNewEd.cpp
        tabs/MTab.cpp
        tabs/MTabsController.cpp

        network/NCrypt.cpp
        network/Network.cpp
        network/NSync.cpp

        storage/SMigrations.cpp
        storage/Storage.cpp
        storage/SSecure.cpp

        storage/migrations/SMVer1.cpp

        utils/ULoginDialog.cpp
        utils/UPassDialog.cpp
        utils/UScrollArea.cpp
        utils/USingleton.cpp
        utils/UTray.cpp

        widgets/WMain.cpp
        widgets/WSync.cpp
        widgets/WTabs.cpp
        )


SET(M_H
        vars.h

        crypt/CAes.h
        crypt/CRsa.h
        crypt/CTools.h

        tabs/editors/MEdTab.h

        tabs/links/MLink.h
        tabs/links/MGroup.h

        tabs/lists/MLsTab.h

        tabs/MNewEd.h
        tabs/MTab.h
        tabs/MTabsController.h

        network/NCrypt.h
        network/Network.h
        network/NSync.h

        storage/SMigrations.h
        storage/Storage.h
        storage/SSecure.h

        storage/migrations/SMigration.h
        storage/migrations/SMVer1.h

        utils/ULoginDialog.h
        utils/UPassDialog.h
        utils/UScrollArea.h
        utils/USingleton.h
        utils/UTray.h

        widgets/WMain.h
        widgets/WSync.h
        widgets/WTabs.h
        )

add_subdirectory(vendor/markdown)

qt5_wrap_cpp(GENERATED_SOURCES ${M_H})
qt5_add_resources(UI_RESOURCES res/res.qrc)

add_executable(Organizer ${M_S} ${M_H} ${UI_RESOURCES})
qt5_use_modules(Organizer Core Widgets Network)

target_link_libraries(Organizer ${Qt5Core_QTMAIN_LIBRARIES} qca-qt5 MarkToHtml)
