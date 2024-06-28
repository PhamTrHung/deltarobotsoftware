/********************************************************************************
** Form generated from reading UI file 'hsvwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HSVWINDOW_H
#define UI_HSVWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_HSVWindow
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QVBoxLayout *verticalLayout_2;
    QSlider *sldMinH;
    QSlider *sldMaxH;
    QSlider *sldMinS;
    QSlider *sldMaxS;
    QSlider *sldMinV;
    QSlider *sldMaxV;
    QVBoxLayout *verticalLayout_3;
    QLabel *lblMinH;
    QLabel *lblMaxH;
    QLabel *lblMinS;
    QLabel *lblMaxS;
    QLabel *lblMinV;
    QLabel *lblMaxV;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnObject1;
    QPushButton *btnObject2;
    QPushButton *btnObject3;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *leObject1Name;
    QLineEdit *leObject2Name;
    QLineEdit *leObject3Name;

    void setupUi(QDialog *HSVWindow)
    {
        if (HSVWindow->objectName().isEmpty())
            HSVWindow->setObjectName("HSVWindow");
        HSVWindow->resize(305, 338);
        HSVWindow->setMaximumSize(QSize(600, 800));
        gridLayout = new QGridLayout(HSVWindow);
        gridLayout->setObjectName("gridLayout");
        groupBox = new QGroupBox(HSVWindow);
        groupBox->setObjectName("groupBox");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
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

        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");

        verticalLayout->addWidget(label_6);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        sldMinH = new QSlider(groupBox);
        sldMinH->setObjectName("sldMinH");
        sldMinH->setMaximum(255);
        sldMinH->setValue(100);
        sldMinH->setTracking(true);
        sldMinH->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(sldMinH);

        sldMaxH = new QSlider(groupBox);
        sldMaxH->setObjectName("sldMaxH");
        sldMaxH->setMaximum(255);
        sldMaxH->setValue(150);
        sldMaxH->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(sldMaxH);

        sldMinS = new QSlider(groupBox);
        sldMinS->setObjectName("sldMinS");
        sldMinS->setMaximum(255);
        sldMinS->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(sldMinS);

        sldMaxS = new QSlider(groupBox);
        sldMaxS->setObjectName("sldMaxS");
        sldMaxS->setMaximum(255);
        sldMaxS->setValue(255);
        sldMaxS->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(sldMaxS);

        sldMinV = new QSlider(groupBox);
        sldMinV->setObjectName("sldMinV");
        sldMinV->setMaximum(255);
        sldMinV->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(sldMinV);

        sldMaxV = new QSlider(groupBox);
        sldMaxV->setObjectName("sldMaxV");
        sldMaxV->setMaximum(255);
        sldMaxV->setValue(255);
        sldMaxV->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(sldMaxV);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        lblMinH = new QLabel(groupBox);
        lblMinH->setObjectName("lblMinH");

        verticalLayout_3->addWidget(lblMinH);

        lblMaxH = new QLabel(groupBox);
        lblMaxH->setObjectName("lblMaxH");

        verticalLayout_3->addWidget(lblMaxH);

        lblMinS = new QLabel(groupBox);
        lblMinS->setObjectName("lblMinS");

        verticalLayout_3->addWidget(lblMinS);

        lblMaxS = new QLabel(groupBox);
        lblMaxS->setObjectName("lblMaxS");

        verticalLayout_3->addWidget(lblMaxS);

        lblMinV = new QLabel(groupBox);
        lblMinV->setObjectName("lblMinV");

        verticalLayout_3->addWidget(lblMinV);

        lblMaxV = new QLabel(groupBox);
        lblMaxV->setObjectName("lblMaxV");

        verticalLayout_3->addWidget(lblMaxV);


        horizontalLayout->addLayout(verticalLayout_3);


        horizontalLayout_2->addLayout(horizontalLayout);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        btnObject1 = new QPushButton(HSVWindow);
        btnObject1->setObjectName("btnObject1");
        btnObject1->setFocusPolicy(Qt::NoFocus);
        btnObject1->setStyleSheet(QString::fromUtf8("\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:rgb(255, 255, 0);\n"
"}"));

        horizontalLayout_3->addWidget(btnObject1);

        btnObject2 = new QPushButton(HSVWindow);
        btnObject2->setObjectName("btnObject2");
        btnObject2->setFocusPolicy(Qt::NoFocus);
        btnObject2->setStyleSheet(QString::fromUtf8("\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:rgb(255, 255, 0);\n"
"}"));

        horizontalLayout_3->addWidget(btnObject2);

        btnObject3 = new QPushButton(HSVWindow);
        btnObject3->setObjectName("btnObject3");
        btnObject3->setFocusPolicy(Qt::NoFocus);
        btnObject3->setStyleSheet(QString::fromUtf8("\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:rgb(255, 255, 0);\n"
"}"));

        horizontalLayout_3->addWidget(btnObject3);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        leObject1Name = new QLineEdit(HSVWindow);
        leObject1Name->setObjectName("leObject1Name");
        leObject1Name->setEnabled(true);
        leObject1Name->setFrame(true);
        leObject1Name->setReadOnly(true);

        horizontalLayout_4->addWidget(leObject1Name);

        leObject2Name = new QLineEdit(HSVWindow);
        leObject2Name->setObjectName("leObject2Name");
        leObject2Name->setReadOnly(true);

        horizontalLayout_4->addWidget(leObject2Name);

        leObject3Name = new QLineEdit(HSVWindow);
        leObject3Name->setObjectName("leObject3Name");
        leObject3Name->setReadOnly(true);

        horizontalLayout_4->addWidget(leObject3Name);


        gridLayout->addLayout(horizontalLayout_4, 2, 0, 1, 1);


        retranslateUi(HSVWindow);

        QMetaObject::connectSlotsByName(HSVWindow);
    } // setupUi

    void retranslateUi(QDialog *HSVWindow)
    {
        HSVWindow->setWindowTitle(QCoreApplication::translate("HSVWindow", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("HSVWindow", "HSV", nullptr));
        label->setText(QCoreApplication::translate("HSVWindow", "min H", nullptr));
        label_2->setText(QCoreApplication::translate("HSVWindow", "maxH", nullptr));
        label_3->setText(QCoreApplication::translate("HSVWindow", "min S", nullptr));
        label_4->setText(QCoreApplication::translate("HSVWindow", "max S", nullptr));
        label_5->setText(QCoreApplication::translate("HSVWindow", "min V", nullptr));
        label_6->setText(QCoreApplication::translate("HSVWindow", "max V", nullptr));
        lblMinH->setText(QCoreApplication::translate("HSVWindow", "100", nullptr));
        lblMaxH->setText(QCoreApplication::translate("HSVWindow", "150", nullptr));
        lblMinS->setText(QCoreApplication::translate("HSVWindow", "0", nullptr));
        lblMaxS->setText(QCoreApplication::translate("HSVWindow", "255", nullptr));
        lblMinV->setText(QCoreApplication::translate("HSVWindow", "0", nullptr));
        lblMaxV->setText(QCoreApplication::translate("HSVWindow", "255", nullptr));
        btnObject1->setText(QCoreApplication::translate("HSVWindow", "Add Object 1", nullptr));
        btnObject2->setText(QCoreApplication::translate("HSVWindow", "Add Object 2", nullptr));
        btnObject3->setText(QCoreApplication::translate("HSVWindow", "Add Object 3", nullptr));
        leObject1Name->setText(QCoreApplication::translate("HSVWindow", "KitKat 1", nullptr));
        leObject2Name->setText(QCoreApplication::translate("HSVWindow", "KitKat 2", nullptr));
        leObject3Name->setText(QCoreApplication::translate("HSVWindow", "KitKat 3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HSVWindow: public Ui_HSVWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HSVWINDOW_H
