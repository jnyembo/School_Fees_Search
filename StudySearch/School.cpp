#include "School.h"

#include <vector>


School::School()
	: School("N/A", "N/A", 0.0, "N/A", "N/A", "N/A", "N/A")
{
}

School::School(QString name, QString id, double tuition, QString ville, QString prov, QString type, QString ptpd)
	: mName { name }
	, mID { id }
	, mTuitionFees { tuition }
	, mVillage { ville }
	, mProvince { prov }
	, mType { type }
	, mPTPD { ptpd }
{
}

School School::operator=(const School& rhs)
{
	mName = rhs.Name();
	mID = rhs.ID();
	mTuitionFees = rhs.TuitionFees();
	mVillage = rhs.Village();
	mProvince = rhs.Province();
	mType = rhs.Type();
	mPTPD = rhs.PTPD();

	return (*this);
}

QString School::Name() const
{
	return mName;
}

QString School::ID() const
{
	return mID;
}

double School::TuitionFees() const
{
	return mTuitionFees;
}

QString School::Village() const
{
	return mVillage;
}

QString School::Province() const
{
	return mProvince;
}

QString School::Type() const
{
	return mType;
}

QString School::PTPD() const
{
	return mProvince;
}
