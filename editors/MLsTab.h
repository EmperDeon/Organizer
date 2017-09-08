#ifndef ORGANIZER_MLSTAB_H
#define ORGANIZER_MLSTAB_H

#include <editors/MTabsController.h>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QLineEdit>

class MTab;
class MLsTab;
class MListEF;


class MLsTab : public MTab {
	QJsonObject obj;

	QVBoxLayout *list;
	MListEF *events;
	QScrollArea *scroll;

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

	QLineEdit *getLineEdit(int i) const;
};


class MListEF : public QObject {
	MLsTab *par;

public:
	explicit MListEF(MLsTab *t) : par(t) {}

	bool eventFilter(QObject *object, QEvent *qEvent) override;
};


#endif //ORGANIZER_MLSTAB_H
