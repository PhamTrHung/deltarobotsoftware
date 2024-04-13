/********************************************************************************
** Form generated from reading UI file 'connectionsettings.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTIONSETTINGS_H
#define UI_CONNECTIONSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ConnectionSettings
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *btnApply;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QVBoxLayout *verticalLayout_2;
    QComboBox *cmbCom;
    QComboBox *cmbBaudrate;
    QComboBox *cmbDataBits;
    QComboBox *cmbParity;
    QComboBox *cmbStopBits;

    void setupUi(QDialog *ConnectionSettings)
    {
        if (ConnectionSettings->objectName().isEmpty())
            ConnectionSettings->setObjectName("ConnectionSettings");
        ConnectionSettings->resize(262, 242);
        gridLayout_2 = new QGridLayout(ConnectionSettings);
        gridLayout_2->setObjectName("gridLayout_2");
        groupBox = new QGroupBox(ConnectionSettings);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        btnApply = new QPushButton(groupBox);
        btnApply->setObjectName("btnApply");

        gridLayout->addWidget(btnApply, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, -1, 0, -1);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(-1, 0, 0, 0);
        label = new QLabel(groupBox);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");

        verticalLayout->addWidget(label_5);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, -1, 0, -1);
        cmbCom = new QComboBox(groupBox);
        cmbCom->setObjectName("cmbCom");

        verticalLayout_2->addWidget(cmbCom);

        cmbBaudrate = new QComboBox(groupBox);
        cmbBaudrate->addItem(QString());
        cmbBaudrate->addItem(QString());
        cmbBaudrate->addItem(QString());
        cmbBaudrate->setObjectName("cmbBaudrate");

        verticalLayout_2->addWidget(cmbBaudrate);

        cmbDataBits = new QComboBox(groupBox);
        cmbDataBits->addItem(QString());
        cmbDataBits->addItem(QString());
        cmbDataBits->setObjectName("cmbDataBits");

        verticalLayout_2->addWidget(cmbDataBits);

        cmbParity = new QComboBox(groupBox);
        cmbParity->addItem(QString());
        cmbParity->addItem(QString());
        cmbParity->addItem(QString());
        cmbParity->setObjectName("cmbParity");

        verticalLayout_2->addWidget(cmbParity);

        cmbStopBits = new QComboBox(groupBox);
        cmbStopBits->addItem(QString());
        cmbStopBits->addItem(QString());
        cmbStopBits->setObjectName("cmbStopBits");

        verticalLayout_2->addWidget(cmbStopBits);


        horizontalLayout->addLayout(verticalLayout_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 2);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(ConnectionSettings);

        QMetaObject::connectSlotsByName(ConnectionSettings);
    } // setupUi

    void retranslateUi(QDialog *ConnectionSettings)
    {
        ConnectionSettings->setWindowTitle(QCoreApplication::translate("ConnectionSettings", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ConnectionSettings", "Select parameters", nullptr));
        btnApply->setText(QCoreApplication::translate("ConnectionSettings", "Apply", nullptr));
        label->setText(QCoreApplication::translate("ConnectionSettings", "COM:", nullptr));
        label_2->setText(QCoreApplication::translate("ConnectionSettings", "Baud rate:", nullptr));
        label_3->setText(QCoreApplication::translate("ConnectionSettings", "Data bits:", nullptr));
        label_4->setText(QCoreApplication::translate("ConnectionSettings", "Parity: ", nullptr));
        label_5->setText(QCoreApplication::translate("ConnectionSettings", "Stop bits:", nullptr));
        cmbBaudrate->setItemText(0, QCoreApplication::translate("ConnectionSettings", "9600", nullptr));
        cmbBaudrate->setItemText(1, QCoreApplication::translate("ConnectionSettings", "115200", nullptr));
        cmbBaudrate->setItemText(2, QCoreApplication::translate("ConnectionSettings", "38400", nullptr));

        cmbDataBits->setItemText(0, QCoreApplication::translate("ConnectionSettings", "8", nullptr));
        cmbDataBits->setItemText(1, QCoreApplication::translate("ConnectionSettings", "7", nullptr));

        cmbParity->setItemText(0, QCoreApplication::translate("ConnectionSettings", "None", nullptr));
        cmbParity->setItemText(1, QCoreApplication::translate("ConnectionSettings", "RTS/CTS", nullptr));
        cmbParity->setItemText(2, QCoreApplication::translate("ConnectionSettings", "XON/XOFF", nullptr));

        cmbStopBits->setItemText(0, QCoreApplication::translate("ConnectionSettings", "1", nullptr));
        cmbStopBits->setItemText(1, QCoreApplication::translate("ConnectionSettings", "2", nullptr));

    } // retranslateUi

};

namespace Ui {
    class ConnectionSettings: public Ui_ConnectionSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTIONSETTINGS_H
