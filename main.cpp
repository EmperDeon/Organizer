#include <QtWidgets/QApplication>
#include <QtCore/QFile>
#include <widgets/WMain.h>
#include <QtWidgets/QFileDialog>
#include <storage/SFile.h>
#include <widgets/WFiles.h>

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

    auto *w = new WFiles(Storage::getFiles("test_name"));
    w->show();

//    auto *f = Storage::getFiles("test_name");
//
//    f->saveFile(QFileDialog::getExistingDirectory(wnd), f->getFiles().first());
//
//    Storage::getInstance()->saveJson();

//    QString file = QFileDialog::getOpenFileName(new QWidget);
//    SFile f_info(file);
//
//    qDebug() << f_info.hash;

//	CFiles::copyToEncryptedStorage("path/to/dir", QFileDialog::getOpenFileName(wnd));
//	CFiles::copyFromEncryptedStorage("path/to/dir", "всё.rar", QFileDialog::getExistingDirectory(wnd));

//    qDebug() << ULoginDialog::getLoginHash();

//	Network net;
//	qDebug() << net.request("documents/last_timestamp");

//    a.closeAllWindows();
	return a.exec();
}

void operator delete(void *p, std::size_t /*unused*/) {
	std::free(p);
}

void operator delete[](void *p, std::size_t /*unused*/) {
	std::free(p);
}
