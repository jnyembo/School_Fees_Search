/********************************************************************************
** Form generated from reading UI file 'StudySearch.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUDYSEARCH_H
#define UI_STUDYSEARCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StudySearchClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *StudySearchClass)
    {
        if (StudySearchClass->objectName().isEmpty())
            StudySearchClass->setObjectName("StudySearchClass");
        StudySearchClass->resize(600, 400);
        menuBar = new QMenuBar(StudySearchClass);
        menuBar->setObjectName("menuBar");
        StudySearchClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(StudySearchClass);
        mainToolBar->setObjectName("mainToolBar");
        StudySearchClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(StudySearchClass);
        centralWidget->setObjectName("centralWidget");
        StudySearchClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(StudySearchClass);
        statusBar->setObjectName("statusBar");
        StudySearchClass->setStatusBar(statusBar);

        retranslateUi(StudySearchClass);

        QMetaObject::connectSlotsByName(StudySearchClass);
    } // setupUi

    void retranslateUi(QMainWindow *StudySearchClass)
    {
        StudySearchClass->setWindowTitle(QCoreApplication::translate("StudySearchClass", "StudySearch", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StudySearchClass: public Ui_StudySearchClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUDYSEARCH_H
