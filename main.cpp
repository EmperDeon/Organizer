#include <QtWidgets/QApplication>
#include <QtCore/QFile>
#include <widgets/WMain.h>
#include <crypt/CFiles.h>
#include <QtWidgets/QFileDialog>

int main(int argc, char **argv) {
	QApplication a(argc, argv);
	QCA::Initializer init;

	QFile File(":/style.qss");
	File.open(QFile::ReadOnly);
	QString StyleSheet = QLatin1String(File.readAll());
	a.setStyleSheet(StyleSheet);

    qApp->setWindowIcon(QIcon(":/icon.ico"));

	auto *wnd = WMain::getInstance();
//	wnd->show();

//	CFiles::copyToEncryptedStorage("path/to/dir", QFileDialog::getOpenFileName(wnd));
	CFiles::copyFromEncryptedStorage("path/to/dir", "всё.rar", QFileDialog::getExistingDirectory(wnd));

	qDebug() << "Finished";

//    qDebug() << ULoginDialog::getLoginHash();

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
