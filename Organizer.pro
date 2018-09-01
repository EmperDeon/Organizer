TEMPLATE = app
TARGET   = Organizer

QT += core network widgets

CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14


ORGANIZER_MAJOR_VERSION = 0
ORGANIZER_MINOR_VERSION = 2
ORGANIZER_PATCH_VERSION = 0
ORGANIZER_VERSION_STRING = "$${ORGANIZER_MAJOR_VERSION}.$${ORGANIZER_MINOR_VERSION}.$${ORGANIZER_PATCH_VERSION}"

DEFINES += "VERSION_MAJOR=$$ORGANIZER_MAJOR_VERSION" \
	   "VERSION_MINOR=$$ORGANIZER_MINOR_VERSION" \
	   "VERSION_BUILD=$$ORGANIZER_PATCH_VERSION" \
	   "VERSION=\\\"$$ORGANIZER_VERSION_STRING\\\"" \
       "USE_LTM" \
       "LTM_DESC" \


SOURCES += main.cpp \
 crypt/CAes.cpp \
 crypt/CRsa.cpp \
 crypt/Crypt.cpp \
 crypt/CBytes.cpp \
 utils/Utils.cpp \
 \
 tabs/editors/TEditor.cpp \
 \
 tabs/encrypted/TEncryptedTab.cpp \
 \
 tabs/journals/TJournalTab.cpp \
 \
 tabs/files/TFileGroup.cpp \
 \
 tabs/links/TLink.cpp \
 tabs/links/TLinksGroup.cpp \
 \
 tabs/TabNew.cpp \
 tabs/Tab.cpp \
 tabs/TabsController.cpp \
 tabs/TList.cpp \
 \
 network/NCrypt.cpp \
 network/Network.cpp \
 network/NSync.cpp \
 \
 plugins/Plugin.cpp \
 plugins/tabs/PTabPlugin.cpp \
 plugins/tabs/PTabFile.cpp \
 plugins/tabs/PTabFiles.cpp \
 \
 storage/SBackup.cpp \
 storage/SGroups.cpp \
 storage/SMap.cpp \
 storage/SMigrations.cpp \
 storage/Storage.cpp \
 storage/SSecure.cpp \
 storage/SSettings.cpp \
 \
 storage/migrations/SMVer0.cpp \
 storage/migrations/SMVer01.cpp \
 storage/migrations/SMVer02.cpp \
 \
 utils/ULoginDialog.cpp \
 utils/UPassDialog.cpp \
 utils/UScrollArea.cpp \
 utils/USingleton.cpp \
 utils/UTray.cpp \
 \
 utils/logs/ULogger.cpp \
 \
 utils/widgets/dates/UDateItem.cpp \
 utils/widgets/UCenteredWidget.cpp \
 utils/widgets/UDateDialog.cpp \
 utils/widgets/UDatesWidget.cpp \
 utils/widgets/UTreeWidget.cpp \
 \
 widgets/files/WFile.cpp \
 widgets/files/WFileIcon.cpp \
 widgets/files/WFiles.cpp \
 \
 widgets/groups/WTGroupLabel.cpp \
 widgets/groups/WTGroups.cpp \
 \
 widgets/settings/WSCheckBox.cpp \
 widgets/settings/WSComboBox.cpp \
 widgets/settings/WSettings.cpp \
 widgets/settings/WSetting.cpp \
 widgets/settings/WSLineEdit.cpp \
 \
 widgets/sort/WTSorter.cpp \
 \
 widgets/WMain.cpp \
 widgets/WSync.cpp \
 widgets/WTabs.cpp \
 \
 vendor/additions.cpp



HEADERS += vars.h \
 crypt/CAes.h \
 crypt/CRsa.h \
 crypt/Crypt.h \
 crypt/CBytes.h \
 utils/Utils.h \
  \
 tabs/editors/TEditor.h \
  \
 tabs/encrypted/TEncryptedTab.h \
  \
 tabs/files/TFileGroup.h \
  \
 tabs/journals/TJournalTab.h \
  \
 tabs/links/TLink.h \
 tabs/links/TLinksGroup.h \
  \
 tabs/TabNew.h \
 tabs/Tab.h \
 tabs/TabsController.h \
 tabs/TList.h \
  \
 network/NCrypt.h \
 network/Network.h \
 network/NSync.h \
  \
 plugins/Plugin.h \
 plugins/tabs/PTabPlugin.h \
 plugins/tabs/PTabFile.h \
 plugins/tabs/PTabFiles.h \
  \
 storage/SBackup.h \
 storage/SGroups.h \
 storage/SMap.h \
 storage/SMigrations.h \
 storage/Storage.h \
 storage/SSecure.h \
 storage/SSettings.h \
  \
 storage/migrations/SMigration.h \
 storage/migrations/SMVer0.h \
 storage/migrations/SMVer01.h \
 storage/migrations/SMVer02.h \
  \
 utils/ULoginDialog.h \
 utils/UOrderedMap.h \
 utils/UPassDialog.h \
 utils/UScrollArea.h \
 utils/USingleton.h \
 utils/UTray.h \
  \
 utils/logs/ULogger.h \
  \
 utils/widgets/dates/UDateItem.h \
 utils/widgets/UCenteredWidget.h \
 utils/widgets/UDateDialog.h \
 utils/widgets/UDatesWidget.h \
 utils/widgets/UTreeWidget.h \
  \
 widgets/files/WFile.h \
 widgets/files/WFileIcon.h \
 widgets/files/WFiles.h \
  \
 widgets/groups/WTGroupLabel.h \
 widgets/groups/WTGroups.h \
  \
 widgets/settings/WSCheckBox.h \
 widgets/settings/WSComboBox.h \
 widgets/settings/WSettings.h \
 widgets/settings/WSetting.h \
 widgets/settings/WSLineEdit.h \
  \
 widgets/sort/WTSorter.h \
  \
 widgets/WMain.h \
 widgets/WSync.h \
 widgets/WTabs.h \
  \
 vendor/additions.h


RC_FILE = res.rc
RESOURCES += res/res.qrc

win32: LIBS += -L$$PWD/vendor/win_libs32/
else:unix: LIBS += -L$$PWD/vendor/libs/

LIBS += -lmarkdown -lboost_regex -ltomcrypt -ltommath -lcrypto -lssl

INCLUDEPATH += $$PWD/vendor/
DEPENDPATH += $$PWD/vendor/win_libs32/
