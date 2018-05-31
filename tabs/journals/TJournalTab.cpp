/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <crypt/CAes.h>
#include <QDebug>
#include <vendor/additions.h>
#include "TJournalTab.h"

TJournalTab::TJournalTab(const QJsonObject &o) : MTab(o, MTab::Journal) {
    auto *l = new QVBoxLayout;

    // Top menu
    auto *m_l = new QHBoxLayout;
    m_l->setAlignment(Qt::AlignRight | Qt::AlignTop);

    m_buttons = new QButtonGroup;

    auto icons = {":/icons/md-edit.png", ":/icons/md-view.png"};

    int i = 0;
    for (QString f : icons) {
        auto b = new QPushButton(QIcon(f), "");

        b->setFixedSize(20, 20);
        b->setProperty("transparentBackground", true);
        b->setCheckable(true);

        m_buttons->addButton(b, i++);
        m_l->addWidget(b);
    }
    m_buttons->setExclusive(true);

    connect(m_buttons, static_cast<void (QButtonGroup::*)(int, bool)>(&QButtonGroup::buttonToggled), this,
            &TJournalTab::changeMode);


    l->addLayout(m_l);
    // Top menu

    // Editor
    dates = new UDatesWidget;

    m_layout = new QHBoxLayout;

    edit = new QPlainTextEdit;
    view = new QTextEdit;

    dates->setWithName(true);
    dates->setFixedWidth(300);
    edit->setTabStopWidth(15);
//    view->setWordWrap(true);

    QFile File(":/md-style.css");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    view->document()->setDefaultStyleSheet(StyleSheet);
    view->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

    view->setAlignment(Qt::AlignTop);
    view->setReadOnly(true);

    m_layout->addWidget(dates);
    m_layout->addWidget(edit);
    m_layout->addWidget(view);

    connect(edit, &QPlainTextEdit::textChanged, this, &TJournalTab::updateText);

    connect(dates, &UDatesWidget::createdDate, this, &TJournalTab::createdDate);
    connect(dates, &UDatesWidget::changedDate, this, &TJournalTab::changedDate);
    connect(dates, &UDatesWidget::removedDate, this, &TJournalTab::removedDate);
    connect(dates, &UDatesWidget::selectedDate, this, &TJournalTab::selectedDate);

    l->addLayout(m_layout);
    // Editor

    load();

    m_buttons->button(cur_mode)->setChecked(true);
    changeMode(cur_mode, true);

    setLayout(l);
}

void TJournalTab::fromJson(QJsonValue v) {
    entries = Utils::fromJson(v.toString());

    if (!entries.isEmpty()) {
        QMap<QString, UDateItem *> dates_map;

        for (const QString &id : entries.keys())
            dates_map[id] = new UDateItem(id, entries[id].toObject()["name"].toString(), additionalInfo(id));

        dates->load(dates_map);

        dates->selectDate(entries.keys().last());
    }
}

QJsonValue TJournalTab::toJson() {
    saveDate(dates->currentDate());

    return Utils::toJson(entries);
}

void TJournalTab::loadCustomParams(const QJsonObject &o) {
    cur_mode = o["mode"].toInt();
}

void TJournalTab::saveCustomParams(QJsonObject &o) {
    o["mode"] = cur_mode;
}

void TJournalTab::updateText() {
    std::string md = edit->toPlainText().toStdString();

    md = md2html(md);
    md = "<body>" + md + "</body>";

    view->setText(QString::fromStdString(md));
}

void TJournalTab::changeMode(int id, bool checked) {
    if (!checked)
        return;

    cur_mode = id;

    switch (id) {
        case 0:
            edit->setVisible(true);
            view->setVisible(false);
            break;

        case 1:
            edit->setVisible(false);
            view->setVisible(true);
            break;

        default:;
    }
}

void TJournalTab::loadDate(const QString &name) {
    const QJsonObject &date = entries[name].toObject();

    edit->setPlainText(date["content"].toString());
}

void TJournalTab::saveDate(const QString &id) {
    if (!id.isEmpty()) {
        QJsonObject date = entries[id].toObject();

//        qDebug() << "Saving: " << id << ", data:" << date;

        date["content"] = edit->toPlainText();

        entries[id] = date;
    }
}

void TJournalTab::createdDate(UDateItem *item) {
    entries[item->id()] = QJsonObject{
            {"name", item->name()}
    };

//    qDebug() << "Created with: " << item->id() << ", name: " << item->name();

    item->setContents(item->id(), item->name(), additionalInfo(item->id()));

    dates->addItem(item);
}

void TJournalTab::changedDate(const QString &old_id, UDateItem *item) {
//    qDebug() << old_id << " " << item->id();

    if (old_id != item->id()) {
        entries[item->id()] = entries[old_id];
        entries.remove(old_id);
    }

    QJsonObject obj = entries[item->id()].toObject();

    obj["name"] = item->name();
    entries[item->id()] = obj;
}

void TJournalTab::removedDate(const QString &name) {
    entries.remove(name);
}

void TJournalTab::selectedDate(const QString &from, const QString &to) {
//    qDebug() << "Selected: " << from << ", to: " << to;

    saveDate(from);

    loadDate(to);
}

QStringList TJournalTab::additionalInfo(const QString &id) {
    Q_UNUSED(id);
    return QStringList();
}
