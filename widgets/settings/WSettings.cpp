/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QVBoxLayout>
#include <storage/SSettings.h>
#include <QtWidgets/QLabel>
#include <QtCore/QVariant>
#include <QtCore/QDebug>
#include <utils/UScrollArea.h>
#include <QtWidgets/QPushButton>
#include "WSettings.h"
#include "WSCheckBox.h"
#include "WSLineEdit.h"
#include "WSComboBox.h"

WSettings::WSettings() {
    auto *l = new QVBoxLayout;

    scroll = new QVBoxLayout;
    auto w_scroll = new UScrollArea(scroll);

    const QJsonArray &levels = SSettings::allSettings();
    for (const auto &t_level : levels) {
        const QJsonObject level = t_level.toObject();

        auto *l_level = new QLabel(level["name"].toString());
        l_level->setProperty("class", "h2");
        scroll->addWidget(l_level);

        for (const auto &t_entry : level["entries"].toArray()) {
            auto *entry = createWidgetForType(t_entry.toObject());

            if (entry != nullptr) {
                entries << entry;
                scroll->addWidget(entry);
            }
        }
    }

    l->addWidget(w_scroll);

    auto *h_l = new QHBoxLayout;
    auto *b_save = new QPushButton(tr("Save settings")), *b_exit = new QPushButton(tr("Cancel"));

    connect(b_save, &QPushButton::clicked, this, &WSettings::save);
    connect(b_exit, &QPushButton::clicked, [this]() { this->close(); });

    h_l->addWidget(b_save);
    h_l->addWidget(b_exit);
    l->addLayout(h_l);

    setLayout(l);
}

WSetting *WSettings::createWidgetForType(const QJsonObject &obj) {
    const QString &type = obj["type"].toString();
    WSetting *r;

    if (type == "boolean") {
        r = new WSCheckBox(obj);

    } else if (type == "string" || type == "list") {
        r = new WSLineEdit(obj);

    } else if (type == "integer") {
        r = new WSLineEdit(obj, WSLineEdit::Integer);

    } else if (type == "select") {
        r = new WSComboBox(obj);

    } else {
        r = nullptr;
        qWarning() << "Unknown setting type: " << type;
    }

    return r;
}

void WSettings::save() {
//    qDebug() << "Saving settings";

    for (auto *entry : entries) {
        SSettings::set(entry->name(), entry->value());
    }
}
