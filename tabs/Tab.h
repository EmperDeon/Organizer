/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_TAB_H
#define ORGANIZER_TAB_H

#include <QtWidgets/QWidget>
#include <QtCore/QJsonObject>
#include <QtCore/QMap>
#include <vendor/additions.h>


class Tab : public QWidget {
public:
	enum TabType : int {
		Text = 1,
        LinksGroup = 2,
        FilesGroup = 4,
        Journal = 8,
		Encrypted = 512,
		NewTab = 1024
	};

private:
	qint64 u_time = 0, u_last = 0;
	bool timer_not_started = true;
    json_o obj;

	TabType type = NewTab;

protected:
    QString t_name, t_uuid;
    int t_sort_id;

	void saveStorage();

public:
    explicit Tab() = default;

    explicit Tab(const json_o &o, TabType t = NewTab);

    void load(json_o o = json_o());

	QJsonObject save();

	void updated();

	QString name() { return t_name; }

    QString uuid() { return t_uuid; }

    int sortId() { return t_sort_id; }

    const QString desc();


	static const QString tabTypeS(TabType type);

    inline static const QString tabTypeS(const json_o &tab) { return tabTypeS(tabType(tab)); }

    inline static TabType tabType(const json_o &tab) { return tabType(tab["type"].is_number() ? tab["type"] : 1024); }

    inline static TabType tabType(int t) { return static_cast<Tab::TabType>(t); }


    virtual void fromJson(json v) { Q_UNUSED(v); };

    virtual json toJson() { return json_o(); };

    virtual void loadCustomParams(const json_o &o) { Q_UNUSED(o); }

    virtual void saveCustomParams(json_o &o) { Q_UNUSED(o); }

    virtual void onSelected() {}

	friend class TEncryptedTab;
};


#endif //ORGANIZER_TAB_H
