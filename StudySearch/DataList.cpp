#include "DataList.h"

#include "xlsxdocument.h"
#include <QtXml>

#include <vector>
#include <algorithm>
#include <QStringList>

void DataList::Init()
{
	QTXMLGLOBAL_H

	QString fileName = "School infos.xlsx";
	QXlsx::Document myDocument(fileName);
	
	QStringList SheetNames;
	SheetNames = myDocument.sheetNames();
	
	for (size_t i{}; i < SheetNames.size(); ++i) {
		myDocument.selectSheet(SheetNames[i]);
		mProvinces.push_back(Province(SheetNames[i]));

		int rowCount = myDocument.dimension().rowCount();
		int colCount = myDocument.dimension().columnCount();

		QStringList ListofValues;
		// Parcourir les cellules de la feuille
		for (size_t row = 1; row <= rowCount; ++row) {
			for (size_t col = 1; col <= colCount; ++col) {
				// Obtenir la valeur de la cellule
				QVariant value = myDocument.read(row, col);


				//QString valueToString = value.toString(); // Convertir le QVariant en QString
				ListofValues.resize(col);
				ListofValues[col - 1] = value.toString();
			}
			if (row > 1) {
				//Ajoute chaque évole pour chaque province!
				mProvinces[i].Schools().push_back(School(ListofValues[0],
					ListofValues[1], ListofValues[5].toDouble(), ListofValues[2],
					SheetNames[i], ListofValues[4], ListofValues[3]));
			}
			//Libere la liste des valeurs lues dans le fichier excel
			ListofValues.clear();
		}

	}

	sort(); // On tri les provinces par ordre alphabetique
}

void DataList::sort()
{
	std::sort(mProvinces.begin(), mProvinces.end(), [](const Province& p1, const Province& p2) 
		{
			return p1.Name() < p2.Name();
		});
}

std::vector<Province>& DataList::Provinces()
{
	return mProvinces;
}
