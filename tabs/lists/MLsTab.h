#ifndef ORGANIZER_MLSTAB_H
#define ORGANIZER_MLSTAB_H

#include <QtCore/QJsonArray>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QLineEdit>
#include <utils/UScrollArea.h>
#include <tabs/MTab.h>

class MListEF;


class MLsTab : public MTab {
	QVBoxLayout *list;
	QList<QLineEdit *> lines;

	MListEF *events;

public:
	explicit MLsTab(const QJsonObject &o);

	QString getDesc() override;

	void importFrom(QString s) override;

	QString exportTo() override;

	void fromJson(QJsonValue v) override;

	QJsonValue toJson() override;


	void addLine(QString text = "");

	void delChild(QLineEdit *t);

	void returnPressed(QLineEdit *l);

	void arrowPressed(QLineEdit *l, bool up);
};


class MListEF : public QObject {
	MLsTab *tab;

public:
	explicit MListEF(MLsTab *t) : tab(t) {}

	bool eventFilter(QObject *object, QEvent *qEvent) override;
};


#endif //ORGANIZER_MLSTAB_H
