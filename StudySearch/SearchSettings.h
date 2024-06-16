#pragma once

#ifndef SEARCHSETTINGS_H
#define SEARCHSETTINGS_H

#include <QString>
#include <QLineEdit>


class SearchSettings
{
public:
	SearchSettings();
	~SearchSettings();

	void setup(QString Budget, QString Prov, QString ville, QString type);
	void reset();
	QString Budget() const ;
	QString Province() const;
	QString Ville() const ;
	QString Type()const;

private:
	QString mBudget;
	QString mProvince;
	QString mVille;
	QString mType;


};



#endif //!SEARCHSETTINGS_H


