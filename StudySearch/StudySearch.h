#pragma once

#ifndef STUDY_SEARCH_H
#define STUDY_SEARCH_H

#include <QtWidgets/QMainWindow>
#include "ui_StudySearch.h"

#include <QHBoxLayout>
#include <QFormLayout>
#include <QTabWidget>
#include <QRadioButton>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>

#include"EngineSearch.h"
#include"SearchSettings.h"

class StudySearch : public QMainWindow
{
    Q_OBJECT

public:
    StudySearch(QWidget *parent = nullptr);
    ~StudySearch();

    void setTableStyle(QTableWidget* & table);
    void insertTableTitle(QTableWidget* & table);

public slots :
    void startSearchPushed();

public slots:
    void resetSystemPushed();

private:
    Ui::StudySearchClass ui;




    int rowCount;
    int colCount;

    QHBoxLayout * mMainLayout;
    QTabWidget* mProvTab;
    QRadioButton* mColButton;
    QRadioButton* mUniButton;
    QLineEdit* mBudget;
    QLineEdit* mProvince;
    QLineEdit* mVille;
    QPushButton* mStartButton;
    QPushButton* mResetButton;

    EngineSearch mEngine;
    SearchSettings mParameters;
};

#endif // !STUDY_SEARCH_H

