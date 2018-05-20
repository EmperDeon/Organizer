#
# Copyright (c) 2017 by Ilya Barykin
# Released under the MIT License.
# See the provided LICENSE.TXT file for details.
#

cmake_minimum_required(VERSION 3.0)
project(Organizer CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/vendor")

set(ORGANIZER_MAJOR_VERSION "0")
set(ORGANIZER_MINOR_VERSION "1")
set(ORGANIZER_PATCH_VERSION "0")
set(ORGANIZER_VERSION_STRING "${ORGANIZER_MAJOR_VERSION}.${ORGANIZER_MINOR_VERSION}.${ORGANIZER_PATCH_VERSION}")

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets)
find_package(Qt5Network)
find_package(Qca-qt5)

configure_file(vars.h.in vars.h)

SET(M_S
        main.cpp
        res.rc

        crypt/CAes.cpp
        crypt/CRsa.cpp
        crypt/CTools.cpp

        tabs/editors/MEdTab.cpp

        tabs/encrypted/TEncryptedTab.cpp

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
        storage/SSettings.cpp

        storage/migrations/SMVer1.cpp
        storage/migrations/SMVer11.cpp

        utils/ULoginDialog.cpp
        utils/UPassDialog.cpp
        utils/UScrollArea.cpp
        utils/USingleton.cpp
        utils/UTray.cpp

        utils/logs/ULogger.cpp

        utils/widgets/dates/UDateItem.cpp
        utils/widgets/UCenteredWidget.cpp
        utils/widgets/UDateDialog.cpp
        utils/widgets/UDatesWidget.cpp
        utils/widgets/UTreeWidget.cpp

        widgets/files/WFile.cpp
        widgets/files/WFileIcon.cpp
        widgets/files/WFiles.cpp

        widgets/groups/WTGroupLabel.cpp
        widgets/groups/WTGroups.cpp

        widgets/settings/WSCheckBox.cpp
        widgets/settings/WSComboBox.cpp
        widgets/settings/WSettings.cpp
        widgets/settings/WSetting.cpp
        widgets/settings/WSLineEdit.cpp

        widgets/sort/WTSorter.cpp

        widgets/WMain.cpp
        widgets/WSync.cpp
        widgets/WTabs.cpp

        vendor/additions.cpp
        )


SET(M_H
        vars.h

        crypt/CAes.h
        crypt/CRsa.h
        crypt/CTools.h

        tabs/editors/MEdTab.h

        tabs/encrypted/TEncryptedTab.h

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
        storage/SSettings.h

        storage/migrations/SMigration.h
        storage/migrations/SMVer1.h
        storage/migrations/SMVer11.h

        utils/ULoginDialog.h
        utils/UPassDialog.h
        utils/UScrollArea.h
        utils/USingleton.h
        utils/UTray.h

        utils/logs/ULogger.h

        utils/widgets/dates/UDateItem.h
        utils/widgets/UCenteredWidget.h
        utils/widgets/UDateDialog.h
        utils/widgets/UDatesWidget.h
        utils/widgets/UTreeWidget.h

        widgets/files/WFile.h
        widgets/files/WFileIcon.h
        widgets/files/WFiles.h

        widgets/groups/WTGroupLabel.h
        widgets/groups/WTGroups.h

        widgets/settings/WSCheckBox.h
        widgets/settings/WSComboBox.h
        widgets/settings/WSettings.h
        widgets/settings/WSetting.h
        widgets/settings/WSLineEdit.h

        widgets/sort/WTSorter.h

        widgets/WMain.h
        widgets/WSync.h
        widgets/WTabs.h

        vendor/additions.h
        )

add_subdirectory(vendor)
include(cotire/CMake/cotire)

include_directories(vendor/simple_ossl/include)

qt5_wrap_cpp(GENERATED_SOURCES ${M_H})
qt5_add_resources(UI_RESOURCES res/res.qrc)

add_executable(Organizer ${M_S} ${M_H} ${UI_RESOURCES})
qt5_use_modules(Organizer Core Widgets Network)

target_link_libraries(Organizer ${Qt5Core_QTMAIN_LIBRARIES} qca-qt5 cpp-markdown simple-ossl)

cotire(Organizer)
