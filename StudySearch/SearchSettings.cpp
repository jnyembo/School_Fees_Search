#include "SearchSettings.h"

SearchSettings::SearchSettings()
	: mBudget {""}
	, mProvince {""}
	, mVille {""}
	, mType {""}
{
}

SearchSettings::~SearchSettings()
{
}

void SearchSettings::setup(QString Budget, QString Prov, QString ville, QString type)
{
	mBudget = Budget;
	mProvince = Prov;
	mVille = ville;
	mType = type;
}

void SearchSettings::reset()
{
	mBudget.clear();
	mProvince.clear();
	mVille.clear();
	mType.clear();
}

QString SearchSettings::Budget() const
{
	return mBudget;
}

QString SearchSettings::Province() const
{
	return mProvince;
}

QString SearchSettings::Ville() const
{
	return mVille;
}

QString SearchSettings::Type() const
{
	return mType;
}

