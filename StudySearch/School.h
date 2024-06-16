#pragma once

#ifndef SCHOOL_H
#define SCHOOL_H


#include "xlsxdocument.h"
#include <QtXml>

#include <QString>

#include <vector>

class School
{
public:
	School();
	School(QString name, QString id, double tuition, 
		QString ville, QString prov, QString type, QString ptpd);
	~School() = default;

	School operator=(const School& rhs);

	QString Name() const;
	QString ID() const;
	double TuitionFees() const;
	QString Village() const;
	QString Province() const;
	QString Type() const;
	QString PTPD() const;


private:
	QString mName;
	QString mID;
	double mTuitionFees;
	QString mVillage;
	QString mProvince;
	QString mType;
	QString mPTPD;
	//std::vector<QString> mProgram;
};



#endif //!SCHOOL_H


