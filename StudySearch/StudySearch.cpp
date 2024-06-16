#include "StudySearch.h"

#include "xlsxdocument_p.h"
#include "xlsxdocument.h"
#include <QtXml>
#include <iostream>
#include <QtGlobal>
#include <QCoreApplication>
#include <QtCore>


#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QTableWidget>
#include <QFormLayout>
#include <QTabWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QGroupBox>
#include <QVariantList>
#include <QPushButton>



#include "DataList.h"

StudySearch::StudySearch(QWidget *parent)
    : QMainWindow(parent)
    , mMainLayout{ new QHBoxLayout }
    //, mProVLayout { new QFormLayout }
    , mEngine { mParameters }
    , mProvTab { new QTabWidget }
    , mColButton{ new QRadioButton }
    , mUniButton{ new QRadioButton }
    , mBudget { new QLineEdit }
    , mProvince { new QLineEdit }
    , mVille { new QLineEdit }
    , mStartButton { new QPushButton}
    , mResetButton { new QPushButton}
    , rowCount { 0 }
    , colCount { 0 }
{ 
    ui.setupUi(this);

    //On ajoute les tabs en fonction des provinces
    QWidget* centralWidget = new QWidget(this);
    
    QTXMLGLOBAL_H

    for (size_t i{}; i < mEngine.Provinces().size(); ++i) {

        QTabWidget* tab = new QTabWidget;
        mProvTab->addTab(new QWidget, mEngine.Provinces()[i].Name());

        // Le nom du fichier Excel à ouvrir
        QString fileName = "School infos.xlsx";
        // Créer un objet QXlsx::Document avec le nom du fichier
        QXlsx::Document xlsx(fileName);

        QGridLayout* DataGridLayout{ new QGridLayout };
        // Le nom de la feuille à lire
        QString sheetName = mEngine.Provinces()[i].Name();
        // Sélectionner la feuille à lire
        xlsx.selectSheet(sheetName);

        // Obtenir le nombre de lignes et de colonnes de la feuille
        rowCount = xlsx.dimension().rowCount();
        colCount = xlsx.dimension().columnCount();

        QTableWidget* table{ new QTableWidget(rowCount, colCount)};
        // Parcourir les cellules de la feuille
        for (int row = 1; row <= rowCount; ++row) {
            for (int col = 1; col <= colCount; ++col) {
                // Obtenir la valeur de la cellule
                table->setItem(row - 1, col - 1, new QTableWidgetItem(xlsx.read(row, col).toString()));
            }
        }

        setTableStyle(table); //On applique le style du tableau
        table->resizeColumnsToContents();
        DataGridLayout->addWidget(table);
        QHBoxLayout* dLayout{ new QHBoxLayout};
        dLayout->addLayout(DataGridLayout);
        QWidget* pageWidget = mProvTab->widget(i);

        if (pageWidget) {
            pageWidget->setLayout(dLayout);
        }
    }

    mProvTab->setStyleSheet("background-color: #AED6F1;");
    QVBoxLayout* tabprov = new QVBoxLayout;
    tabprov->addWidget(mProvTab);

    //On defini le frame et les paramètres à rentrer
    QGroupBox* ParamFrame{ new QGroupBox("Parametres") };
    QVBoxLayout* prLayout = new QVBoxLayout;
    QFormLayout* paramLayout{ new QFormLayout};
    ParamFrame->setFixedWidth(250);
    ParamFrame->setStyleSheet("background-color: #AED6F1;");
    ParamFrame->setLayout(paramLayout);
    prLayout->addWidget(ParamFrame);

    paramLayout->addRow("Budget", mBudget);
    paramLayout->addRow("Province", mProvince);
    paramLayout->addRow("Ville", mVille);
    mColButton->setChecked(true); // College par default
    paramLayout->addRow("College", mColButton);
    paramLayout->addRow("Universite", mUniButton);

    mStartButton->setText("START");
    mResetButton->setText("RESET");
    paramLayout->addRow(mStartButton);
    paramLayout->addRow(mResetButton);


    paramLayout->setHorizontalSpacing(10);
    paramLayout->setVerticalSpacing(10);
    QVBoxLayout* dataLayout{ new QVBoxLayout };
    dataLayout->addLayout(tabprov);
    
    //**** LES CONNEXIONS ****
    connect(mStartButton, &QPushButton::pressed, this, &StudySearch::startSearchPushed);
    connect(mResetButton, &QPushButton::pressed, this, &StudySearch::resetSystemPushed);


    mMainLayout->addLayout(prLayout);
    mMainLayout->addLayout(dataLayout);
    setLayout(mMainLayout);
    centralWidget->setLayout(mMainLayout);
    setCentralWidget(centralWidget);
}

StudySearch::~StudySearch()
{}

void StudySearch::setTableStyle(QTableWidget* & table)
{
    QString styleFilePath = "style.qss";
    QFile styleFile(styleFilePath);
    styleFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleFile.readAll());
    styleFile.close();

    table->setStyleSheet(styleSheet);

    // Appliquer un style différent à chaque ligne paire
    for (int row = 0; row < table->rowCount(); ++row) {
        if (row % 2 == 1) { // Ligne impaire
            for (int col = 0; col < table->columnCount(); ++col) {
                QTableWidgetItem* item = table->item(row, col);
                do {
                    QTableWidgetItem* it = table->item(0, col);
                    it->setBackground(QBrush(QColor(100, 100, 255)));
                } while (row == 0);
                if (item) {
                    item->setBackground(QBrush(QColor(200, 220, 255)));
                }
            }
        }
    }
}


void StudySearch::startSearchPushed()
{
    if(mEngine.mSolution.empty() and mBudget->text() != "" and mProvince->text() != "") {
        QString type;
        if (mColButton->isChecked()) {
            type = "College";
        }
        else {
            type = "Universite";
        }
        mParameters.setup(mBudget->text(), mProvince->text(), mVille->text(), type);
        mEngine.Start();

        // Créez un nouvel onglet "Solution"
        QWidget* solutionTab = new QWidget;
        QVBoxLayout* solutionLayout = new QVBoxLayout;
        QGridLayout* SolGridLayout{ new QGridLayout };

        int rowC = mEngine.mSolution.size();
        QTableWidget* table{ new QTableWidget(rowC, colCount)};

        insertTableTitle(table);
        // Parcourir les cellules de la feuille
        for (int row = 1; row <= rowC; ++row) {
            for (int col = 1; col <= colCount; ++col) {
                //Si aucune information n'a été trouvée
                if (mEngine.NothingFound()) {
                    table->setRowCount(2);
                    table->setItem(row, col - 1, new QTableWidgetItem("Aucun information trouvee"));
                    setTableStyle(table);
                }
                else {
                    // Obtenir la valeur de la cellule
                    QString data;

                    switch (col - 1) {
                    case 0://Saisi le nom de l'établissement
                        table->setItem(row, col - 1, new QTableWidgetItem(mEngine.mSolution[row - 1].Name()));
                        setTableStyle(table);
                        break;
                    case 1://Saisi le EED
                        table->setItem(row, col - 1, new QTableWidgetItem(mEngine.mSolution[row - 1].ID()));
                        setTableStyle(table);
                        break;
                    case 2://Saisi la ville
                        table->setItem(row, col - 1, new QTableWidgetItem(mEngine.mSolution[row - 1].Village()));
                        setTableStyle(table);
                        break;
                    case 3://Saisi PTPD
                        table->setItem(row, col - 1, new QTableWidgetItem(mEngine.mSolution[row - 1].PTPD()));
                        setTableStyle(table);
                        break;
                    case 4://Saisi le Type
                        table->setItem(row, col - 1, new QTableWidgetItem(mEngine.mSolution[row - 1].Type()));
                        setTableStyle(table);
                        break;
                    case 5://Saisi Frais
                        data = QString::number(mEngine.mSolution[static_cast<std::vector<School, std::allocator<School>>::size_type>(row) - 1].TuitionFees());
                        table->setItem(row, col - 1, new QTableWidgetItem(data));
                        setTableStyle(table);
                        break;
                    //case 6://Saisi Langue
                    //    table->setItem(row, col - 1, new QTableWidgetItem(mEngine.mSolution[row - 1].));
                    //    setTableStyle(table);
                    //    break;
                    //case 7://Saisi Langue
                    //    table->setItem(row, col - 1, new QTableWidgetItem(mEngine.mSolution[row - 1].));
                    //    setTableStyle(table);
                    //    break;
                    default:
                        break;
                    }
                    
                }

            }
        }

        table->resizeColumnsToContents();
        SolGridLayout->addWidget(table);
        solutionLayout->addLayout(SolGridLayout);

        solutionTab->setLayout(solutionLayout);

        // Remplacez le contenu de l'onglet "Resultat"
        mProvTab->removeTab(mProvTab->indexOf(solutionTab));
        mProvTab->insertTab(0, solutionTab, "Resultat");

        // Cachez les autres onglets pour montrer uniquement l'onglet "Resultat"
        for (int i = 1; i < mProvTab->count(); ++i) {
            mProvTab->setTabEnabled(i, false);
        }

        // Sélectionnez l'onglet "Resultat"
        mProvTab->setCurrentIndex(0);
    }
    
}

void StudySearch::resetSystemPushed()
{
    if ( ! mEngine.mSolution.empty()) {
        mEngine.reset();
        mParameters.reset();
        // Réactivez tous les onglets et supprimez l'onglet "Resultat"
        for (int i = 0; i < mProvTab->count(); ++i) {
            mProvTab->setTabEnabled(i, true);
        }
        mProvTab->removeTab(0); // Supprimez l'onglet "Resultat"
    }
    
}

void StudySearch::insertTableTitle(QTableWidget*& table)
{
    table->setItem(0, 0, new QTableWidgetItem("Nom de l etablissement"));
    table->setItem(0, 1, new QTableWidgetItem("No d etablissement  (EED)"));
    table->setItem(0, 2, new QTableWidgetItem("Ville"));
    table->setItem(0, 3, new QTableWidgetItem("Admissibles au PTPD"));
    table->setItem(0, 4, new QTableWidgetItem("Type"));
    table->setItem(0, 5, new QTableWidgetItem("Frais de Scolarite"));
    table->setItem(0, 6, new QTableWidgetItem("Langue"));
    table->setItem(0, 7, new QTableWidgetItem("Informations supplementaires"));
}



