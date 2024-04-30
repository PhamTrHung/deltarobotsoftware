/********************************************************************************
** Form generated from reading UI file 'gcodewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GCODEWINDOW_H
#define UI_GCODEWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_GCodeWindow
{
public:
    QTextEdit *teGcode;
    QPushButton *btnSaveGcodeTe;
    QGroupBox *groupBox;
    QPushButton *btnAddGcode;
    QComboBox *cmbGcodeCmd;
    QLabel *lbX;
    QLineEdit *leXValue;
    QLineEdit *leYValue;
    QLabel *lbY;
    QLineEdit *leZValue;
    QLabel *lbZ;
    QLineEdit *leVValue;
    QLabel *lbV;
    QLineEdit *leAValue;
    QLabel *lbA;
    QComboBox *cmbProgramList;
    QPushButton *btnFormat;

    void setupUi(QDialog *GCodeWindow)
    {
        if (GCodeWindow->objectName().isEmpty())
            GCodeWindow->setObjectName("GCodeWindow");
        GCodeWindow->setWindowModality(Qt::NonModal);
        GCodeWindow->resize(350, 370);
        GCodeWindow->setMinimumSize(QSize(350, 370));
        GCodeWindow->setMaximumSize(QSize(350, 370));
        GCodeWindow->setFocusPolicy(Qt::NoFocus);
        teGcode = new QTextEdit(GCodeWindow);
        teGcode->setObjectName("teGcode");
        teGcode->setGeometry(QRect(10, 100, 331, 231));
        btnSaveGcodeTe = new QPushButton(GCodeWindow);
        btnSaveGcodeTe->setObjectName("btnSaveGcodeTe");
        btnSaveGcodeTe->setGeometry(QRect(270, 340, 71, 25));
        btnSaveGcodeTe->setMinimumSize(QSize(0, 25));
        btnSaveGcodeTe->setMaximumSize(QSize(16777215, 25));
        btnSaveGcodeTe->setFocusPolicy(Qt::NoFocus);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/disk.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSaveGcodeTe->setIcon(icon);
        groupBox = new QGroupBox(GCodeWindow);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 10, 331, 81));
        btnAddGcode = new QPushButton(groupBox);
        btnAddGcode->setObjectName("btnAddGcode");
        btnAddGcode->setGeometry(QRect(90, 50, 91, 24));
        btnAddGcode->setFocusPolicy(Qt::NoFocus);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnAddGcode->setIcon(icon1);
        cmbGcodeCmd = new QComboBox(groupBox);
        cmbGcodeCmd->addItem(QString());
        cmbGcodeCmd->addItem(QString());
        cmbGcodeCmd->addItem(QString());
        cmbGcodeCmd->addItem(QString());
        cmbGcodeCmd->addItem(QString());
        cmbGcodeCmd->setObjectName("cmbGcodeCmd");
        cmbGcodeCmd->setGeometry(QRect(10, 20, 61, 22));
        lbX = new QLabel(groupBox);
        lbX->setObjectName("lbX");
        lbX->setGeometry(QRect(80, 20, 16, 21));
        QFont font;
        font.setPointSize(13);
        lbX->setFont(font);
        lbX->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));
        leXValue = new QLineEdit(groupBox);
        leXValue->setObjectName("leXValue");
        leXValue->setGeometry(QRect(90, 20, 31, 21));
        leYValue = new QLineEdit(groupBox);
        leYValue->setObjectName("leYValue");
        leYValue->setGeometry(QRect(140, 20, 31, 21));
        leYValue->setFocusPolicy(Qt::StrongFocus);
        leYValue->setAutoFillBackground(false);
        leYValue->setInputMethodHints(Qt::ImhNone);
        leYValue->setFrame(true);
        leYValue->setClearButtonEnabled(false);
        lbY = new QLabel(groupBox);
        lbY->setObjectName("lbY");
        lbY->setGeometry(QRect(130, 20, 16, 21));
        lbY->setFont(font);
        lbY->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));
        leZValue = new QLineEdit(groupBox);
        leZValue->setObjectName("leZValue");
        leZValue->setGeometry(QRect(190, 20, 31, 21));
        lbZ = new QLabel(groupBox);
        lbZ->setObjectName("lbZ");
        lbZ->setGeometry(QRect(180, 20, 16, 21));
        lbZ->setFont(font);
        lbZ->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));
        leVValue = new QLineEdit(groupBox);
        leVValue->setObjectName("leVValue");
        leVValue->setGeometry(QRect(240, 20, 31, 21));
        lbV = new QLabel(groupBox);
        lbV->setObjectName("lbV");
        lbV->setGeometry(QRect(230, 20, 16, 21));
        lbV->setFont(font);
        lbV->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));
        leAValue = new QLineEdit(groupBox);
        leAValue->setObjectName("leAValue");
        leAValue->setGeometry(QRect(290, 20, 31, 21));
        lbA = new QLabel(groupBox);
        lbA->setObjectName("lbA");
        lbA->setGeometry(QRect(280, 20, 16, 21));
        lbA->setFont(font);
        lbA->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));
        lbA->raise();
        lbV->raise();
        lbZ->raise();
        lbY->raise();
        btnAddGcode->raise();
        cmbGcodeCmd->raise();
        lbX->raise();
        leXValue->raise();
        leYValue->raise();
        leZValue->raise();
        leVValue->raise();
        leAValue->raise();
        cmbProgramList = new QComboBox(GCodeWindow);
        cmbProgramList->addItem(QString());
        cmbProgramList->addItem(QString());
        cmbProgramList->addItem(QString());
        cmbProgramList->addItem(QString());
        cmbProgramList->addItem(QString());
        cmbProgramList->addItem(QString());
        cmbProgramList->setObjectName("cmbProgramList");
        cmbProgramList->setGeometry(QRect(10, 340, 81, 22));
        btnFormat = new QPushButton(GCodeWindow);
        btnFormat->setObjectName("btnFormat");
        btnFormat->setGeometry(QRect(180, 340, 75, 24));
        btnFormat->setFocusPolicy(Qt::NoFocus);

        retranslateUi(GCodeWindow);

        QMetaObject::connectSlotsByName(GCodeWindow);
    } // setupUi

    void retranslateUi(QDialog *GCodeWindow)
    {
        GCodeWindow->setWindowTitle(QCoreApplication::translate("GCodeWindow", "Dialog", nullptr));
        btnSaveGcodeTe->setText(QCoreApplication::translate("GCodeWindow", "Save", nullptr));
        groupBox->setTitle(QCoreApplication::translate("GCodeWindow", "Add G-Code", nullptr));
        btnAddGcode->setText(QCoreApplication::translate("GCodeWindow", "Add Gcode", nullptr));
        cmbGcodeCmd->setItemText(0, QCoreApplication::translate("GCodeWindow", "G01", nullptr));
        cmbGcodeCmd->setItemText(1, QCoreApplication::translate("GCodeWindow", "G02", nullptr));
        cmbGcodeCmd->setItemText(2, QCoreApplication::translate("GCodeWindow", "G03", nullptr));
        cmbGcodeCmd->setItemText(3, QCoreApplication::translate("GCodeWindow", "G28", nullptr));
        cmbGcodeCmd->setItemText(4, QCoreApplication::translate("GCodeWindow", "M204", nullptr));

        lbX->setText(QCoreApplication::translate("GCodeWindow", "X", nullptr));
        lbY->setText(QCoreApplication::translate("GCodeWindow", "Y", nullptr));
        lbZ->setText(QCoreApplication::translate("GCodeWindow", "Z", nullptr));
        lbV->setText(QCoreApplication::translate("GCodeWindow", "F", nullptr));
        lbA->setText(QCoreApplication::translate("GCodeWindow", "A", nullptr));
        cmbProgramList->setItemText(0, QString());
        cmbProgramList->setItemText(1, QCoreApplication::translate("GCodeWindow", "Program 1", nullptr));
        cmbProgramList->setItemText(2, QCoreApplication::translate("GCodeWindow", "Program 2", nullptr));
        cmbProgramList->setItemText(3, QCoreApplication::translate("GCodeWindow", "Program 3", nullptr));
        cmbProgramList->setItemText(4, QCoreApplication::translate("GCodeWindow", "Program 4", nullptr));
        cmbProgramList->setItemText(5, QCoreApplication::translate("GCodeWindow", "Program 5", nullptr));

        btnFormat->setText(QCoreApplication::translate("GCodeWindow", "Format", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GCodeWindow: public Ui_GCodeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GCODEWINDOW_H
