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

    json_o res = Network().request("documents/last_timestamp");

    if (res["status"].get<QString>() == "ok") {// && last < res["docs_last"].toString()) {
        res = Network().request("documents/load");

        st->loadDocs(res["docs"]);
        st->set("docs_last", res["docs_last"]);

        contr->load();
    }
}
