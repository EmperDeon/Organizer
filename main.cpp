/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QApplication>
#include <QtCore/QFile>
#include <widgets/WMain.h>
#include <utils/logs/ULogger.h>
#include <QtGui/QFontDatabase>

void initStyles();

int main(int argc, char **argv) {
    QApplication a(argc, argv);

    ULogger::getInstance();

    logI(QString("Version ") + VERSION);

    Crypt::getInstance();
    Storage::getInstance();
    SGroups::getInstance();

    initStyles();

    auto *wnd = WMain::getInstance();
    wnd->show();

//     json &value = Storage::getInstance()->getDocs()["{12099588-f9f7-489e-a61e-85820d0ff067}"]["content"];
//     QString content = value.get<QString>();
//     CAes aes(E_TAB_CIPHER, Crypt::deriveKey("9i8u7y"));
//     QString decrypted_content = aes.decrypt(content);
//     qDebug() << decrypted_content;
//
//     content = Utils::serializeFromString(decrypted_content).toString();
//     value = aes.encrypt(content);
//
//     Storage::getInstance()->saveJson();

    logD("WMain showed");

    return qApp->exec();
}

void initStyles() {
    QFontDatabase::addApplicationFont(":/fonts/PT_Sans-Web-Bold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/PT_Sans-Web-BoldItalic.ttf");
    QFontDatabase::addApplicationFont(":/fonts/PT_Sans-Web-Italic.ttf");
    QFontDatabase::addApplicationFont(":/fonts/PT_Sans-Web-Regular.ttf");
    qApp->setFont(QFont("PT Sans Regular"));

    QFile File(":/style.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QString::fromUtf8(File.readAll());
    qApp->setStyleSheet(StyleSheet);

    qApp->setWindowIcon(QIcon(":/icon.ico"));
}


#ifdef QMAKE_BUILD
void operator delete(void *p, std::size_t /*unused*/) {
    std::free(p);
}

void operator delete(void *p) {
    std::free(p);
}

void operator delete[](void *p, std::size_t /*unused*/) {
    std::free(p);
}

void operator delete[](void *p) {
    std::free(p);
}
#endif


#define JSON_APPEND_CONVERSIONS

#undef JSON_APPEND_CONVERSIONS
