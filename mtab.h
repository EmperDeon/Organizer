#ifndef ORGANIZER_MTAB_H
#define ORGANIZER_MTAB_H

#include <QtWidgets/QWidget>
#include <QtCore/QJsonObject>


class MTab : public QWidget {
	qint64 u_time = 0, u_last = 0;
	bool timer_not_started = true;
	QJsonObject obj;
	QString name;

protected:
	void saveStorage();

public:
	explicit MTab() = default;

	explicit MTab(const QJsonObject &o);

	void load();

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
