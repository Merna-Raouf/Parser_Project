/********************************************************************************
** Form generated from reading UI file 'subwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBWINDOW_H
#define UI_SUBWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_SubWindow
{
public:

    void setupUi(QDialog *SubWindow)
    {
        if (SubWindow->objectName().isEmpty())
            SubWindow->setObjectName(QStringLiteral("SubWindow"));
        SubWindow->resize(400, 300);

        retranslateUi(SubWindow);

        QMetaObject::connectSlotsByName(SubWindow);
    } // setupUi

    void retranslateUi(QDialog *SubWindow)
    {
        SubWindow->setWindowTitle(QApplication::translate("SubWindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SubWindow: public Ui_SubWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBWINDOW_H
