#include <QtWidgets/QApplication>
#include <QtCore/QFile>
#include <widgets/WMain.h>

int main(int argc, char **argv) {
	QApplication a(argc, argv);
	QCA::Initializer init;

	QFile File(":/style.qss");
	File.open(QFile::ReadOnly);
	QString StyleSheet = QLatin1String(File.readAll());
	a.setStyleSheet(StyleSheet);

    qApp->setWindowIcon(QIcon(":/icon.ico"));

	auto *wnd = WMain::getInstance();
    wnd->show();

	return a.exec();
}

void operator delete(void *p, std::size_t /*unused*/) {
	std::free(p);
}

void operator delete[](void *p, std::size_t /*unused*/) {
	std::free(p);
}
