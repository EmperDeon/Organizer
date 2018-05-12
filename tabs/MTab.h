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
		NewTab = 1024
	};

	enum TabGroup : int {
        All = Text | LinksGroup | FilesGroup | Journal,
        Editors = Text,
		Links = LinksGroup,
        Files = FilesGroup,
        Journals = Journal
	};

	const QString NO_GROUP = QObject::tr("Other tabs");

private:
	qint64 u_time = 0, u_last = 0;
	bool timer_not_started = true;
	QJsonObject obj;

	TabType type = NewTab;

protected:
	QString name;
	QStringList t_groups;

	void saveStorage();

public:
	explicit MTab() = default;

	explicit MTab(const QJsonObject &o, TabType t = NewTab);

	void load(QJsonObject o = QJsonObject());

	QJsonObject save();

	void updated();

	QString getName() { return name; }

	bool isInGroup(const QString &gr);

	const QStringList &groups() { return t_groups; }

	void addGroup(const QString &group) { t_groups << group; }

	void removeGroup(const QString &group) { t_groups.removeAll(group); }

    static const QString type_name(const QJsonObject &tab);

    const QString getDesc();

	virtual void fromJson(QJsonValue v) {};

	virtual QJsonValue toJson() { return QJsonObject(); };

	virtual void loadCustomParams(const QJsonObject &o) {}

	virtual void saveCustomParams(QJsonObject &o) {}
};


#endif //ORGANIZER_MTAB_H
