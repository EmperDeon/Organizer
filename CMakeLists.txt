#
# Copyright (c) 2017 by Ilya Barykin
# Released under the MIT License.
# See the provided LICENSE.TXT file for details.
#

cmake_minimum_required(VERSION 3.0)
project(Organizer)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets)
find_package(Qt5Network)
find_package(Qca-qt5)


set(CMAKE_CXX_FLAGS "-std=c++14")


SET(M_S
        main.cpp
        res.rc

        crypt/CAes.cpp
        crypt/CRsa.cpp
        crypt/CTools.cpp

        tabs/editors/MEdTab.cpp

        tabs/journals/TJournalTab.cpp

        tabs/files/MFlGroup.cpp

        tabs/links/MLink.cpp
        tabs/links/MGroup.cpp

        tabs/MNewTab.cpp
        tabs/MTab.cpp
        tabs/MTabsController.cpp

        network/NCrypt.cpp
        network/Network.cpp
        network/NSync.cpp

        plugins/Plugin.cpp
        plugins/tabs/PTabPlugin.cpp
        plugins/tabs/PTabFile.cpp
        plugins/tabs/PTabFiles.cpp

        storage/SBackup.cpp
        storage/SMigrations.cpp
        storage/Storage.cpp
        storage/SSecure.cpp

        storage/migrations/SMVer1.cpp
        storage/migrations/SMVer11.cpp

        utils/ULoginDialog.cpp
        utils/UPassDialog.cpp
        utils/UScrollArea.cpp
        utils/USingleton.cpp
        utils/UTray.cpp

        utils/widgets/dates/UDateItem.cpp
        utils/widgets/UDateDialog.cpp
        utils/widgets/UDatesWidget.cpp
        utils/widgets/UTreeWidget.cpp

        widgets/files/WFile.cpp
        widgets/files/WFileIcon.cpp
        widgets/files/WFiles.cpp

        widgets/sort/WTSorter.cpp

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

        tabs/files/MFlGroup.h

        tabs/journals/TJournalTab.h

        tabs/links/MLink.h
        tabs/links/MGroup.h

        tabs/MNewTab.h
        tabs/MTab.h
        tabs/MTabsController.h

        network/NCrypt.h
        network/Network.h
        network/NSync.h

        plugins/Plugin.h
        plugins/tabs/PTabPlugin.h
        plugins/tabs/PTabFile.h
        plugins/tabs/PTabFiles.h

        storage/SBackup.h
        storage/SMigrations.h
        storage/Storage.h
        storage/SSecure.h

        storage/migrations/SMigration.h
        storage/migrations/SMVer1.h
        storage/migrations/SMVer11.h

        utils/ULoginDialog.h
        utils/UPassDialog.h
        utils/UScrollArea.h
        utils/USingleton.h
        utils/UTray.h

        utils/widgets/dates/UDateItem.h
        utils/widgets/UDateDialog.h
        utils/widgets/UDatesWidget.h
        utils/widgets/UTreeWidget.h

        widgets/files/WFile.h
        widgets/files/WFileIcon.h
        widgets/files/WFiles.h

        widgets/sort/WTSorter.h

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
