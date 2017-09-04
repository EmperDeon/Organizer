#ifndef ORGANIZER_MTAB_H
#define ORGANIZER_MTAB_H

#include <QtWidgets/QWidget>
#include <QtCore/QJsonObject>


class MTab : public QWidget {
public:
    enum TabType : int {
        Text,
        List,
        LinksGroup,

        NewTab = 100
    };

private:
	qint64 u_time = 0, u_last = 0;
	bool timer_not_started = true;
	QJsonObject obj;
	QString name;

    TabType type;

protected:
	void saveStorage();

public:
	explicit MTab() = default;

    explicit MTab(const QJsonObject &o, TabType t = NewTab);

    void load(QJsonObject o = QJsonObject());

	QJsonObject save();

	void updated();

	QString getName() { return name; }

	virtual QString getDesc() = 0;

	virtual void importFrom(QString s) = 0;

	virtual QString exportTo() = 0;

	virtual void fromJson(QJsonValue v) = 0;

	virtual QJsonValue toJson() = 0;


};


#endif //ORGANIZER_MTAB_H
