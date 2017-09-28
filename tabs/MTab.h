#ifndef ORGANIZER_MTAB_H
#define ORGANIZER_MTAB_H

#include <QtWidgets/QWidget>
#include <QtCore/QJsonObject>
#include <QtCore/QMap>


class MTab : public QWidget {
public:
    enum TabType : int {
	    Text = 1,
	    List = 2,
	    LinksGroup = 4,
	    NewTab = 1024
    };

	enum TabGroup : int {
		All = Text | List | LinksGroup,
		Editors = Text | List,
		Links = LinksGroup
	};

private:
	qint64 u_time = 0, u_last = 0;
	bool timer_not_started = true;
	QJsonObject obj;

	TabType type = NewTab;

protected:
	QString name;

	void saveStorage();

public:
	explicit MTab() = default;

    explicit MTab(const QJsonObject &o, TabType t = NewTab);

    void load(QJsonObject o = QJsonObject());

	QJsonObject save();

	void updated();

	QString getName() { return name; }

	bool isInGroup(TabGroup gr) { return gr & type; }

	virtual QString getDesc() = 0;

	virtual void importFrom(QString s) = 0;

	virtual QString exportTo() = 0;

	virtual void fromJson(QJsonValue v) = 0;

	virtual QJsonValue toJson() = 0;

	virtual void loadCustomParams(const QJsonObject &o) {}

	virtual QJsonObject saveCustomParams() { return QJsonObject(); }
};


#endif //ORGANIZER_MTAB_H
