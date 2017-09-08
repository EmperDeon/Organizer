#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <vendor/markdown/markdown.h>
#include "MMdTab.h"

MMdTab::MMdTab(const QJsonObject &o) : MTab(o, MTab::Markdown) {
    auto *l = new QVBoxLayout;

    // Top menu
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
            &MMdTab::changeMode);

    l->addLayout(m_l);
    // Top menu

    // Editor
    m_layout = new QHBoxLayout;

    edit = new QPlainTextEdit;
    view = new QLabel("Rendered Markdown Text");

    edit->setTabStopWidth(15);
    view->setWordWrap(true);

    view_scroll = new QScrollArea;

    view->setAlignment(Qt::AlignTop);
    view_scroll->setWidget(view);
    view_scroll->setWidgetResizable(true);
    view_scroll->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    view_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    view_scroll->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    view_scroll->setFrameStyle(QFrame::NoFrame);


    m_layout->addWidget(edit);
    m_layout->addWidget(view_scroll);

    connect(edit, &QPlainTextEdit::textChanged, this, &MMdTab::updateText);

    l->addLayout(m_layout);
    // Editor

    load();
    m_buttons->button(cur_mode)->setChecked(true);
    changeMode(cur_mode, true);

    setLayout(l);
}

QString MMdTab::getDesc() {
    return "Markdown: " + name;
}

void MMdTab::importFrom(QString s) {
    edit->setPlainText(edit->toPlainText() + "\n" + s);
}

QString MMdTab::exportTo() {
    return edit->toPlainText();
}

void MMdTab::fromJson(QJsonValue v) {
    edit->setPlainText(v.toString());
}

QJsonValue MMdTab::toJson() {
    return edit->toPlainText();
}

void MMdTab::loadCustomParams(const QJsonObject &o) {
    cur_mode = o["mode"].toInt();
}

QJsonObject MMdTab::saveCustomParams() {
    QJsonObject r;

    r["mode"] = cur_mode;

    return r;
}

void MMdTab::updateText() {
    std::string md = edit->toPlainText().toStdString();

    md = markdown::md2html(md);

    view->setText(QString::fromStdString(md));
}

void MMdTab::changeMode(int id, bool checked) {
    if (!checked)
        return;

    cur_mode = id;

    switch (id) {
        case 0:
            edit->setVisible(true);
            view_scroll->setVisible(false);
            break;

        case 1:
            edit->setVisible(true);
            view_scroll->setVisible(true);
            break;

        case 2:
            edit->setVisible(false);
            view_scroll->setVisible(true);
            break;

        default:;
    }

    resizeEvent(nullptr);
}

void MMdTab::resizeEvent(QResizeEvent *event) {
    if (view_scroll->isVisible()) {
        if (edit->isVisible()) {
            int width = this->width() / 2;
            width -= 25;

            view->setFixedWidth(width);
            view_scroll->setFixedWidth(width);

        } else {
            view->setMinimumSize(10, 10);
            view_scroll->setMinimumSize(10, 10);

            view->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
            view_scroll->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
        }
    }

    QWidget::resizeEvent(event);
}

