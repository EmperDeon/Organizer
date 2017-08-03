#include <QtWidgets/QApplication>
#include <QtCore/QFile>
#include <mwgt.h>
#include <Qca-qt5/QtCrypto/QtCrypto>
#include <iostream>
#include <network/Network.h>

int main(int argc, char **argv) {
	QApplication a(argc, argv);
	QCA::Initializer init;

	QFile File(":/style.qss");
	File.open(QFile::ReadOnly);
	QString StyleSheet = QLatin1String(File.readAll());
	a.setStyleSheet(StyleSheet);

	auto *wnd = new MWindow;
	wnd->show();

//	Network net;
//	qDebug() << net.request("documents/last_timestamp");

	return a.exec();
}

void operator delete(void *p, std::size_t /*unused*/) {
	std::free(p);
}

void operator delete[](void *p, std::size_t /*unused*/) {
	std::free(p);
}
