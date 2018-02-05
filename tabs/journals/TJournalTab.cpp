/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <vendor/markdown/markdown.h>
#include <crypt/CAes.h>
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

QString TJournalTab::getDesc() {
    return "Journal: " + name;
}

void TJournalTab::fromJson(QJsonValue v) {
    QString j = v.toString();

    // Check if storage file is encrypted
    if (!(j.isEmpty() || j.startsWith('{'))) {
        CAes aes(JOURNAL_CIPHER, JOURNAL_KEY);

        j = aes.decrypt(j);
    }

    entries = CTools::fromJson(j);

    if (!entries.isEmpty()) {
        QMap<QString, QStringList> dates_map;

        for (const QString &name : entries.keys())
            dates_map[name] = additionalInfo(name);

        dates->load(dates_map);

        dates->selectDate(entries.keys().last());
    }
}

QJsonValue TJournalTab::toJson() {
    saveDate(dates->currentDate());

    QString j = CTools::toJson(entries);

#ifdef ENCRYPT_JOURNAL
    CAes aes(JOURNAL_CIPHER, JOURNAL_KEY);

    j = aes.encrypt(j);
#endif

    return j;
}

void TJournalTab::loadCustomParams(const QJsonObject &o) {
    cur_mode = o["mode"].toInt();
}

void TJournalTab::saveCustomParams(QJsonObject &o) {
    o["mode"] = cur_mode;
}

void TJournalTab::updateText() {
    std::string md = edit->toPlainText().toStdString();

    md = markdown::md2html(md);
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

void TJournalTab::saveDate(const QString &name) {
    if (!name.isEmpty()) {
        QJsonObject date = entries[name].toObject();

        date["content"] = edit->toPlainText();

        entries[name] = date;
    }
}

void TJournalTab::createdDate(const QString &name) {
    entries[name] = {};

    dates->addItem(name, additionalInfo(name));
}

void TJournalTab::changedDate(const QString &old, const QString &name) {
    entries[name] = entries[old];
    entries.remove(old);

    dates->changeDate(name, additionalInfo(name));
}

void TJournalTab::removedDate(const QString &name) {
    entries.remove(name);
}

void TJournalTab::selectedDate(const QString &from, const QString &to) {
    saveDate(from);

    loadDate(to);
}

QStringList TJournalTab::additionalInfo(const QString &name) {
    return QStringList{"tst"};
}
