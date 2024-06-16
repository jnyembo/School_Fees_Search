#include "EngineSearch.h"
#include <QChar>
#include <QString>

EngineSearch::EngineSearch(const SearchSettings& settings)
	: DataList()
	, mSettings { settings }
	, mNothingFound { false }
{
	Init();
}

EngineSearch::~EngineSearch()
{
}

bool EngineSearch::isReady() const
{
	if (mSettings.Budget().isEmpty() or mSettings.Province().isEmpty()) {
		return false;
	}
	else if (isNumeric(mSettings.Budget()) and !isNumeric(mSettings.Province())) {
		return true;
	}
	else {
		return false;
	}
}

bool EngineSearch::isNumeric(QString str) const
{
	for (QChar caractere : str) {
		if (caractere.isLetter()) {
			return false;
		}
	}
	return true;
}

void EngineSearch::Start()
{
	size_t indexProv{};

	if (isReady()) {
		//On recherche la province sp�cifi�e
		for (size_t i{}; i < Provinces().size(); ++i) {
			if (mSettings.Province() == Provinces()[i].Name()) {
				indexProv = i;
				break;
			}
		}
		//
		// Si l'utilisateur n'a pas rentr� la ville
		if (mSettings.Ville() == "") {
			for (size_t i{}; i < Provinces()[indexProv].Schools().size(); ++i) {
				if (mSettings.Budget().toDouble() >= Provinces()[indexProv].Schools()[i].TuitionFees() and
					mSettings.Type() == Provinces()[indexProv].Schools()[i].Type()) {

					mSolution.push_back(Provinces()[indexProv].Schools()[i]);
				}
			}
		}
		//
		// Si l'utilisateur a rentr� la ville
		//On recherche la ville et le budget sp�cifi�
		else {
			for (size_t i{}; i < Provinces()[indexProv].Schools().size(); ++i) {
				if (mSettings.Ville() == Provinces()[indexProv].Schools()[i].Village() and
					mSettings.Budget().toDouble() >= Provinces()[indexProv].Schools()[i].TuitionFees() and
					mSettings.Type() == Provinces()[indexProv].Schools()[i].Type()) {

					mSolution.push_back(Provinces()[indexProv].Schools()[i]);
				}
			}
		}
		
		
	}
	if (mSolution.empty()) {
		mSolution.resize(1);
		mSolution[0] = School();
		mNothingFound = true;
	}
}

void EngineSearch::reset()
{
	mNothingFound = false;
	mSolution.clear();
}

bool EngineSearch::NothingFound() const
{
	return mNothingFound;
}
