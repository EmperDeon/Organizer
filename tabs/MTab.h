/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_MTAB_H
#define ORGANIZER_MTAB_H

#include <QtWidgets/QWidget>
#include <QtCore/QJsonObject>
#include <QtCore/QMap>


class MTab : public QWidget {
public:
	enum TabType : int {
		Text = 1,
        LinksGroup = 2,
        FilesGroup = 4,
        Journal = 8,
		Encrypted = 512,
		NewTab = 1024
	};

	const QString NO_GROUP = QObject::tr("Other tabs");

private:
	qint64 u_time = 0, u_last = 0;
	bool timer_not_started = true;
	QJsonObject obj;

	TabType type = NewTab;

protected:
	QString t_name;
	QStringList t_groups;

	void saveStorage();

public:
	explicit MTab() = default;

	explicit MTab(const QJsonObject &o, TabType t = NewTab);

	void load(QJsonObject o = QJsonObject());

	QJsonObject save();

	void updated();

	QString name() { return t_name; }

	bool isInGroup(const QString &gr);

	const QStringList &groups() { return t_groups; }

	void addGroup(const QString &group) { t_groups << group; }

	void removeGroup(const QString &group) { t_groups.removeAll(group); }

	static const QString tabTypeS(TabType type);

	inline static const QString tabTypeS(const QJsonObject &tab) { return tabTypeS(tabType(tab)); }

	inline static TabType tabType(const QJsonObject &tab) { return tabType(tab["type"].toInt(1024)); }

	inline static TabType tabType(int t) { return static_cast<MTab::TabType>(t); }

	const QString desc();

	virtual void fromJson(QJsonValue v) {};

	virtual QJsonValue toJson() { return QJsonObject(); };

	virtual void loadCustomParams(const QJsonObject &o) {}

	virtual void saveCustomParams(QJsonObject &o) {}

	friend class TEncryptedTab;
};


#endif //ORGANIZER_MTAB_H
