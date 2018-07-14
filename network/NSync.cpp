/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "NSync.h"

NSync::NSync(TabsController *c) : contr(c) {
    timer = new QTimer;

    connect(timer, &QTimer::timeout, this, &NSync::tryLoad);

#ifdef OPTION_SYNC
    timer->start(5000);
#endif
}

void NSync::tryLoad() {
    Storage *st = Storage::getInstance();

    QString last = st->getS("docs_last");

    QJsonObject res = Network().request("documents/last_timestamp").toObject();

    if (res["status"].toString() == "ok") {// && last < res["docs_last"].toString()) {
        res = Network().request("documents/load").toObject();

        st->loadDocs(res["docs"].toString());
        st->set("docs_last", res["docs_last"]);

        contr->load();
    }
}
