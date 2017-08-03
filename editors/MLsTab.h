#ifndef ORGANIZER_MLSTAB_H
#define ORGANIZER_MLSTAB_H

#include <editors/MEditorsController.h>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QLineEdit>

class MTab;

class MOrgContainers;

class MLsTab;

class MListEF;

class MLsTab : public MTab {
Q_OBJECT

	SDocument *cont;
	QJsonObject obj;
	QString name;

	QVBoxLayout *list;
	MListEF *events;
	QScrollArea *scroll;

protected slots:

	void addLine(QString text = "");

public:
	MLsTab(SDocument *c, QJsonObject n);

	QString getDesc() override;

	void save() override;

	void importFrom(QString s) override;

	QString exportTo() override;

	void delChild(QLineEdit *t);

	void returnPressed(QLineEdit *l);

	void arrowPressed(QLineEdit *l, bool up);

	QLineEdit *getLineEdit(int i) const;
};


class MListEF : public QObject {
// Q_OBJECT

	MLsTab *par;

public:
	explicit MListEF(MLsTab *t) : par(t) {}

	bool eventFilter(QObject *object, QEvent *qEvent) override;
};


#endif //ORGANIZER_MLSTAB_H
