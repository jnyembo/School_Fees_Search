#include "Province.h"

#include "xlsxdocument.h"
#include <QtXml>

#include <vector>


Province::Province(QString name)
	: mName { name }
{
}

QString Province::Name() const
{
	return mName;
}

std::vector<School>& Province::Schools()
{
	return mSchools;
}
