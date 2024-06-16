#pragma once

#ifndef PROVINCE_H
#define PROVINCE_H

#include "School.h"
#include <QString>

#include <vector>

class Province
{
public :
	Province() = delete;
	Province(QString name);
	~Province() = default;

	QString Name() const;
	std::vector<School>& Schools();

private:
	QString mName;
	std::vector<School> mSchools;
};



#endif //!PROVINCE_H
