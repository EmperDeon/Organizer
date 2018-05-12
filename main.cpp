/*
	Copyright (c) 2017 by Ilya Barykin
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
    QCA::Initializer init;

    logI(QString("Version ") + VERSION);

    ULogger::getInstance();
    Storage::getInstance();

    initStyles();

    auto *wnd = WMain::getInstance();
    wnd->show();

    logD("WMain showed");

    return a.exec();
}

void initStyles() {
    QFontDatabase::addApplicationFont(":/fonts/PT_Sans-Web-Bold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/PT_Sans-Web-BoldItalic.ttf");
    QFontDatabase::addApplicationFont(":/fonts/PT_Sans-Web-Italic.ttf");
    QFontDatabase::addApplicationFont(":/fonts/PT_Sans-Web-Regular.ttf");
    qApp->setFont(QFont("Roboto Regular"));

    QFile File(":/style.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(StyleSheet);

    qApp->setWindowIcon(QIcon(":/icon.ico"));
}

void operator delete(void *p, std::size_t /*unused*/) {
    std::free(p);
}

void operator delete[](void *p, std::size_t /*unused*/) {
    std::free(p);
}
