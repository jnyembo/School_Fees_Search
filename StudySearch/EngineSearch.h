#pragma once

#ifndef ENGINESEARCH_H
#define ENGINESEARCH_H

#include "DataList.h"
#include"SearchSettings.h"



class EngineSearch : public DataList
{
public: 
	EngineSearch() = delete;
	EngineSearch(const SearchSettings & settings);
	~EngineSearch();

	bool isReady() const;
	void Start();
	void reset();
	bool NothingFound() const;
	std::vector<School> mSolution;

private:
	bool isNumeric(QString str) const;
	const SearchSettings& mSettings;
	bool mNothingFound;
};


#endif //!ENGINESEARCH_H

