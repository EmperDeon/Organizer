#include <QtNetwork/QNetworkRequest>
#include <QtCore/QEventLoop>
#include <QtCore/QTimer>
#include <QtCore/QJsonDocument>
#include <QtNetwork/QHttpPart>
#include <QtCore/QFile>
#include <storage/Storage.h>
#include <QtCore/QJsonArray>
#include "Network.h"

Network::Network() {
	crypt = new NCrypt;
}

QJsonValue Network::request(QString path, QMap<QString, QString> params) {
	QTime requestTime;
	requestTime.start();

	// Join all parameters to string
	QString keys = params.keys().join(", ");

	params.insert("token", Storage::getInstance()->getS("token"));

	QJsonArray tries;
	QJsonValue r = req_POST(path, params);
	while (r.toObject()["error"].toString() == "no_token") {
		tries << r;

//		NAuth::updateToken();
		params.insert("token", Storage::getInstance()->getS("token"));

		r = req_POST(path, params);
	}

	QString r_type = "POST";

	qDebug() << QString("[ %1] '%2'  params: '%3', %4")
			.arg(r_type, 4).arg(path, 22).arg(keys).arg(getLastCode())
			.toStdString().c_str();

	lastTime = requestTime.elapsed();
	writeToLog(path, params, r_type, tries);

	return r;
}

// Request handling
QUrl Network::prepareReq(QString path) {
	QUrl c;

	c.setUrl(NETWORK_URL + path);

	return c;
}

QJsonValue Network::processReq(QNetworkReply *rep) {
	QEventLoop wait;
	QObject::connect(&manager, SIGNAL(finished(QNetworkReply * )), &wait, SLOT(quit()));
	QTimer::singleShot(60000, &wait, SLOT(quit()));
	wait.exec();

	QByteArray data = rep->readAll();
	data = crypt->decrypt(data, rep->url().toString());

	lastReply = QJsonDocument::fromJson(data).object();
	lastError = rep->error();

	rep->deleteLater();

	return lastReply["response"];
}

QJsonValue Network::req_POST(QString path, QMap<QString, QString> params) {
	QNetworkRequest req;
	QNetworkReply *rep;

	req.setUrl(prepareReq(path));

	if (path != "auth/init_network" && path != "auth/check_inited")
		checkEncryption();

	// Collect parameters
	QJsonObject obj;
	for (const QString &k : params.keys())
		obj.insert(k, params[k]);

	// Set required headers
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

	// Get and encrypt data
	QByteArray data = CTools::toJson(obj).toUtf8();
	data = crypt->encrypt(data, path);

	// Send request
	rep = manager.post(req, data);

	return processReq(rep);
}

QJsonValue Network::req_POST(QString path, QHttpMultiPart *m) {
	QNetworkRequest request(prepareReq(path));

	QNetworkReply *rep = manager.post(request, m);
	m->setParent(rep);

	return processReq(rep);
}
// Request handling


QString Network::getLastTime() {
	QString r = QString::number(lastTime);

	if (r.size() > 3) {
		r = r.insert(r.size() - 3, '\'');

	}

	return r + " ms";
}

QString Network::getLastCode() {
	switch (lastError) {
		case QNetworkReply::NoError:
			return "200 OK";
		case QNetworkReply::AuthenticationRequiredError:
			return "401 Auth required";
		case QNetworkReply::ContentNotFoundError:
			return "404 Not found";
		case QNetworkReply::ContentOperationNotPermittedError:
			return "403 || 405 Not permitted";
		case QNetworkReply::UnknownContentError:
			return "422 Validation error";
		case QNetworkReply::InternalServerError:
			return "500 Internal error";

		case QNetworkReply::ProxyAuthenticationRequiredError:
			return "407 ProxyAuthenticationRequired";
		case QNetworkReply::ContentConflictError:
			return "409 ContentConflict";
		case QNetworkReply::ContentGoneError:
			return "410 ContentGone";
		case QNetworkReply::ProtocolInvalidOperationError:
			return "400 ProtocolInvalidOperation";
		case QNetworkReply::OperationNotImplementedError:
			return "501 OperationNotImplemented";
		case QNetworkReply::ServiceUnavailableError:
			return "503 ServiceUnavailable";
		case QNetworkReply::UnknownServerError:
			return "502 .. 511";

		case QNetworkReply::HostNotFoundError:
			return "Error No host";
		case QNetworkReply::ConnectionRefusedError:
			return "Error ConnectionRefused";
		case QNetworkReply::RemoteHostClosedError:
			return "Error RemoteHostClosed";
		case QNetworkReply::TimeoutError:
			return "Error Timeout";
		case QNetworkReply::OperationCanceledError:
			return "Error OperationCanceled";
		case QNetworkReply::SslHandshakeFailedError:
			return "Error SslHandshakeFailed";
		case QNetworkReply::TemporaryNetworkFailureError:
			return "Error TemporaryNetworkFailure";
		case QNetworkReply::NetworkSessionFailedError:
			return "Error NetworkSessionFailed";
		case QNetworkReply::BackgroundRequestNotAllowedError:
			return "Error BackgroundRequestNotAllowed";
		case QNetworkReply::TooManyRedirectsError:
			return "Error TooManyRedirects";
		case QNetworkReply::InsecureRedirectError:
			return "Error InsecureRedirect";
		case QNetworkReply::UnknownNetworkError:
			return "Error UnknownNetwork";
		case QNetworkReply::ProxyConnectionRefusedError:
			return "Error ProxyConnectionRefused";
		case QNetworkReply::ProxyConnectionClosedError:
			return "Error ProxyConnectionClosed";
		case QNetworkReply::ProxyNotFoundError:
			return "Error ProxyNotFound";
		case QNetworkReply::ProxyTimeoutError:
			return "Error ProxyTimeout";
		case QNetworkReply::UnknownProxyError:
			return "Error UnknownProxy";
		case QNetworkReply::ContentAccessDenied:
			return "Error ContentAccessDenied";
		case QNetworkReply::ContentReSendError:
			return "Error ContentReSend";
		case QNetworkReply::ProtocolUnknownError:
			return "Error ProtocolUnknown";
		case QNetworkReply::ProtocolFailure:
			return "Error ProtocolFailure";

		default:
			return "Something else";
	}
}

void Network::uploadFile(QString path, QString file) {
	QString file_name = file.mid(file.lastIndexOf('/'));

	auto *multipart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

	QHttpPart file_part;
	file_part.setHeader(QNetworkRequest::ContentDispositionHeader, R"(form-data; name="img"; filename="")");
	file_part.setHeader(QNetworkRequest::ContentTypeHeader, "image/png");

	auto *f = new QFile(file);
	f->open(QIODevice::ReadOnly);
	file_part.setBodyDevice(f);
	f->setParent(multipart);

	multipart->append(file_part);

	QNetworkRequest request{path};
	QNetworkReply *res = manager.post(request, multipart);
	multipart->setParent(res);

	QEventLoop wait;
	connect(&manager, SIGNAL(finished(QNetworkReply * )), &wait, SLOT(quit()));
	QTimer::singleShot(60000, &wait, SLOT(quit()));
	wait.exec();
}

void Network::checkEncryption() {
	Storage *st = Storage::getInstance();

	QJsonObject ch = req_POST("auth/check_inited", {
			{"uid", st->getS("uid")}
	}).toObject();

	if (ch["error"].toString() == "no_id") {
		st->secureStorage()->initNetworkInfo();

		QJsonObject v = req_POST("auth/init_network", {
				{"uid",    st->getS("uid")},
				{"public", st->getS("rsa_pu")},
				{"aes",    st->getS("net_key")}
		}).toObject();

		qDebug() << v;

		QString status = v["status"].toString();
		if (status == "init_ok") {
			st->set("network_inited", true);
			st->set("server_pub", v["public_key"]);
			st->saveJson();
		}
	}
}

void Network::writeToLog(QString path, QMap<QString, QString> map, QString type, QJsonArray tries) {
	QJsonObject o;

    o["path"] = path;
	o["r_type"] = type;

	o["response"] = lastReply;
	o["code"] = getLastCode();
    o["time"] = getLastTime();
	o["tries"] = tries;

	QJsonObject t;
	for (const QString &k : map.keys()) {
		if (k != "token")
			t[k] = map[k];
	}
	o["params"] = t;

	// Save
	QJsonArray a;
	QFile f("log.json");
	if (f.open(QFile::ReadOnly)) {
		a = QJsonDocument::fromJson(f.readAll()).array();
		f.close();
	}

	a << o;

	f.open(QFile::WriteOnly);
	f.write(QJsonDocument(a).toJson());
	f.close();
}
