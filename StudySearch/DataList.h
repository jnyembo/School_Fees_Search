#pragma once
#ifndef DATALIST_H
#define DATALIST_H

#include "Province.h"

class DataList
{
public:
	DataList() = default;
	~DataList() = default;

	void Init();
	std::vector<Province>& Provinces();

private:
	void sort();
	std::vector<Province> mProvinces;
};

#endif //! DATALIST_H


