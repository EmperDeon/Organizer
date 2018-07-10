/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <vendor/additions.h>
#include "MEdTab.h"

MEdTab::MEdTab(const QJsonObject &o) : MTab(o, MTab::Text) {
    auto *l = new QVBoxLayout;

    // Top menu, TODO: Move to MEdToolbar
    auto *m_l = new QHBoxLayout;
    m_l->setAlignment(Qt::AlignRight | Qt::AlignTop);

    m_buttons = new QButtonGroup;

    auto icons = {":/icons/md-edit.png", ":/icons/md-both.png", ":/icons/md-view.png"};

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
            &MEdTab::changeMode);


    l->addLayout(m_l);
    // Top menu

    // Editor
    m_layout = new QHBoxLayout;

    edit = new QPlainTextEdit;
    view = new QTextEdit;

    edit->setTabStopWidth(15);
//    view->setWordWrap(true);

    QFile File(":/md-style.css");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QString::fromUtf8(File.readAll());
    view->document()->setDefaultStyleSheet(StyleSheet);
    view->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

    view->setAlignment(Qt::AlignTop);
    view->setReadOnly(true);

    m_layout->addWidget(edit);
    m_layout->addWidget(view);

    connect(edit, &QPlainTextEdit::textChanged, this, &MEdTab::updateText);

    l->addLayout(m_layout);
    // Editor

    load();

    m_buttons->button(cur_mode)->setChecked(true);
    changeMode(cur_mode, true);

    setLayout(l);
}

void MEdTab::fromJson(QJsonValue v) {
    edit->setPlainText(v.toString());
}

QJsonValue MEdTab::toJson() {
    return edit->toPlainText();
}

void MEdTab::loadCustomParams(const QJsonObject &o) {
    cur_mode = o["mode"].toInt();
}

void MEdTab::saveCustomParams(QJsonObject &o) {
    o["mode"] = cur_mode;
}

void MEdTab::updateText() {
    std::string md = edit->toPlainText().toStdString();

    md = md2html(md);
    md = "<body>" + md + "</body>";

    view->setText(QString::fromStdString(md));
}

void MEdTab::changeMode(int id, bool checked) {
    if (!checked)
        return;

    cur_mode = id;

    switch (id) {
        case 0:
            edit->setVisible(true);
            view->setVisible(false);
            break;

        case 1:
            edit->setVisible(true);
            view->setVisible(true);
            break;

        case 2:
            edit->setVisible(false);
            view->setVisible(true);
            break;

        default:;
    }
}
