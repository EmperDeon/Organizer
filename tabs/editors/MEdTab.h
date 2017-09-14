#ifndef ORGANIZER_MEDTAB_H
#define ORGANIZER_MEDTAB_H

#include <tabs/MTabsController.h>
#include <QtWidgets/QPlainTextEdit>


class MEdTab : public MTab {
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
