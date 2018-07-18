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
	QJsonObject obj;

	TabType type = NewTab;

protected:
    QString t_name, t_uuid;

	void saveStorage();

public:
    explicit Tab() = default;

    explicit Tab(const QJsonObject &o, TabType t = NewTab);

	void load(QJsonObject o = QJsonObject());

	QJsonObject save();

	void updated();

	QString name() { return t_name; }

    QString uuid() { return t_uuid; }

	static const QString tabTypeS(TabType type);

	inline static const QString tabTypeS(const QJsonObject &tab) { return tabTypeS(tabType(tab)); }

	inline static TabType tabType(const QJsonObject &tab) { return tabType(tab["type"].toInt(1024)); }

    inline static TabType tabType(int t) { return static_cast<Tab::TabType>(t); }

	const QString desc();

	virtual void fromJson(QJsonValue v) { Q_UNUSED(v); };

	virtual QJsonValue toJson() { return QJsonObject(); };

	virtual void loadCustomParams(const QJsonObject &o) { Q_UNUSED(o); }

	virtual void saveCustomParams(QJsonObject &o) { Q_UNUSED(o); }

    virtual void onSelected() {}

	friend class TEncryptedTab;
};


#endif //ORGANIZER_TAB_H
