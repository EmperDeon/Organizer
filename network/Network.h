/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_NETWORK_H
#define ORGANIZER_NETWORK_H

#include <vendor/additions.h>
#include <vendor/additions.h>
#include <QtCore/QMap>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <network/NCrypt.h>

class NCrypt;

class Network : public QObject {
    NCrypt *crypt;

    QNetworkAccessManager manager;

    json_o lastReply;
    int lastTime, lastCode;
    QNetworkReply::NetworkError lastError;


    bool hasErrors();

    QUrl prepareReq(QString path);

    json processReq(QNetworkReply *rep);

    json req_POST(QString path, QMap<QString, QString> params);

    json req_POST(QString path, QHttpMultiPart *part);

//	QString req_GET(QString path, QMap<QString, QString> params);

public:
    Network();

    void uploadFile(QString path, QString file);

    json request(QString path, QMap<QString, QString> params = {});


    QString getLastTime();

    QString getLastCode();

//	QString getParameter(QString par);

    void checkEncryption();

    friend class NAuth;

    void writeToLog(QString qString, QMap<QString, QString> map, QString type, json_a tries = json_a());
};


#endif //ORGANIZER_NETWORK_H
