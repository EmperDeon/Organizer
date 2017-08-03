#ifndef ORGANIZER_MEDTAB_H
#define ORGANIZER_MEDTAB_H

#include <editors/MEditorsController.h>
#include <QtWidgets/QPlainTextEdit>

class MTab;

class MOrgContainers;

class MEdTab;

class MEdTab : public MTab {
	SDocument *cont;
	QJsonObject obj;
	QString name;

	QPlainTextEdit *edit;

public:
	MEdTab(SDocument *c, QJsonObject o);

	QString getDesc() override;

	void save() override;

	void importFrom(QString s) override;

	QString exportTo() override;
};

#endif //ORGANIZER_MEDTAB_H
