/********************************************************************************
** Form generated from reading UI file 'TwixT2.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TWIXT2_H
#define UI_TWIXT2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TwixT2Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TwixT2Class)
    {
        if (TwixT2Class->objectName().isEmpty())
            TwixT2Class->setObjectName("TwixT2Class");
        TwixT2Class->resize(600, 400);
        menuBar = new QMenuBar(TwixT2Class);
        menuBar->setObjectName("menuBar");
        TwixT2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TwixT2Class);
        mainToolBar->setObjectName("mainToolBar");
        TwixT2Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(TwixT2Class);
        centralWidget->setObjectName("centralWidget");
        TwixT2Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TwixT2Class);
        statusBar->setObjectName("statusBar");
        TwixT2Class->setStatusBar(statusBar);

        retranslateUi(TwixT2Class);

        QMetaObject::connectSlotsByName(TwixT2Class);
    } // setupUi

    void retranslateUi(QMainWindow *TwixT2Class)
    {
        TwixT2Class->setWindowTitle(QCoreApplication::translate("TwixT2Class", "TwixT2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TwixT2Class: public Ui_TwixT2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TWIXT2_H
