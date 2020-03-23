/********************************************************************************
** Form generated from reading UI file 'IntersectionGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERSECTIONGUI_H
#define UI_INTERSECTIONGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IntersectionGUIClass
{
public:
    QWidget *centralWidget;
    QPushButton *openFileButton;
    QTextBrowser *pointNumResult;
    QListWidget *allShapes;
    QPushButton *getResult;
    QPushButton *deleteShape;
    QWidget *canvas;
    QPushButton *draw;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *IntersectionGUIClass)
    {
        if (IntersectionGUIClass->objectName().isEmpty())
            IntersectionGUIClass->setObjectName(QString::fromUtf8("IntersectionGUIClass"));
        IntersectionGUIClass->resize(848, 509);
        centralWidget = new QWidget(IntersectionGUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        openFileButton = new QPushButton(centralWidget);
        openFileButton->setObjectName(QString::fromUtf8("openFileButton"));
        openFileButton->setGeometry(QRect(520, 20, 75, 23));
        pointNumResult = new QTextBrowser(centralWidget);
        pointNumResult->setObjectName(QString::fromUtf8("pointNumResult"));
        pointNumResult->setGeometry(QRect(520, 400, 251, 31));
        allShapes = new QListWidget(centralWidget);
        allShapes->setObjectName(QString::fromUtf8("allShapes"));
        allShapes->setGeometry(QRect(520, 60, 251, 321));
        getResult = new QPushButton(centralWidget);
        getResult->setObjectName(QString::fromUtf8("getResult"));
        getResult->setGeometry(QRect(600, 20, 75, 23));
        deleteShape = new QPushButton(centralWidget);
        deleteShape->setObjectName(QString::fromUtf8("deleteShape"));
        deleteShape->setGeometry(QRect(680, 20, 75, 23));
        canvas = new QWidget(centralWidget);
        canvas->setObjectName(QString::fromUtf8("canvas"));
        canvas->setGeometry(QRect(20, 20, 481, 411));
        draw = new QPushButton(centralWidget);
        draw->setObjectName(QString::fromUtf8("draw"));
        draw->setGeometry(QRect(760, 20, 75, 23));
        IntersectionGUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(IntersectionGUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 848, 22));
        IntersectionGUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(IntersectionGUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        IntersectionGUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(IntersectionGUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        IntersectionGUIClass->setStatusBar(statusBar);

        retranslateUi(IntersectionGUIClass);

        QMetaObject::connectSlotsByName(IntersectionGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *IntersectionGUIClass)
    {
        IntersectionGUIClass->setWindowTitle(QCoreApplication::translate("IntersectionGUIClass", "IntersectionGUI", nullptr));
        openFileButton->setText(QCoreApplication::translate("IntersectionGUIClass", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        getResult->setText(QCoreApplication::translate("IntersectionGUIClass", "\346\261\202\350\247\243", nullptr));
        deleteShape->setText(QCoreApplication::translate("IntersectionGUIClass", "\345\210\240\351\231\244\345\233\276\345\275\242", nullptr));
        draw->setText(QCoreApplication::translate("IntersectionGUIClass", "\347\273\230\345\233\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntersectionGUIClass: public Ui_IntersectionGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERSECTIONGUI_H
