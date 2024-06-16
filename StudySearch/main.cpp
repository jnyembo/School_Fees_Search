
#include <QtGlobal>
#include <QCoreApplication>
#include <QtCore>
#include <QtWidgets/QApplication>
#include "xlsxdocument.h"
#include <QtXml>
#include <iostream>
#include <QStyle>
#include "StudySearch.h"



int main(int argc, char* argv[])
{
    //QCoreApplication app(argc, argv);
    QApplication a(argc, argv);
    a.setStyle("Fusion");
    StudySearch w;
    w.setStyleSheet("background-color: #CCCCCC;");
    w.show();
    return a.exec();
}
