/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *WindowClass)
    {
        if (WindowClass->objectName().isEmpty())
            WindowClass->setObjectName(QStringLiteral("WindowClass"));
        WindowClass->resize(600, 400);
        menuBar = new QMenuBar(WindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        WindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(WindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        WindowClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(WindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        WindowClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(WindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        WindowClass->setStatusBar(statusBar);

        retranslateUi(WindowClass);

        QMetaObject::connectSlotsByName(WindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *WindowClass)
    {
        WindowClass->setWindowTitle(QApplication::translate("WindowClass", "Window", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowClass: public Ui_WindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
