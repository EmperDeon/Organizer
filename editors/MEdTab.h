#ifndef ORGANIZER_MEDTAB_H
#define ORGANIZER_MEDTAB_H

#include <editors/MEditorsController.h>
#include <QtWidgets/QPlainTextEdit>

class MTab;
class MEdTab;


class MEdTab : public MTab {
	SDocument *cont;
	QJsonObject obj;
	QString name;

	QPlainTextEdit *edit;

public:
	explicit MEdTab(const QJsonObject &o);

	QString getDesc() override;

	void importFrom(QString s) override;

	QString exportTo() override;

	void fromJson(QJsonValue v) override;

	QJsonValue toJson() override;
};

#endif //ORGANIZER_MEDTAB_H
