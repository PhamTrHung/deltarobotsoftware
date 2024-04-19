/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "camerawidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_7;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QGridLayout *gridLayout;
    QLabel *label_16;
    QWidget *tab1;
    QGroupBox *groupBox_2;
    QPushButton *btnSetSpeedConveyor;
    QPushButton *btnTurnOffConveyor;
    QPushButton *btnTurnOnConveyor;
    QLineEdit *leSpeedConveyor;
    QTabWidget *tabWidget_2;
    QWidget *tab;
    QWidget *t2D;
    QGroupBox *groupBox_6;
    QSlider *sldZAdjustion;
    QWidget *wg2d;
    QPushButton *btnVacuum;
    QLabel *label_15;
    QGroupBox *gbMotionControl;
    QPushButton *btnGo;
    QPushButton *btnForward;
    QPushButton *btnLeft;
    QPushButton *btnRight;
    QPushButton *btnBackward;
    QGroupBox *groupBox_4;
    QLabel *label_8;
    QLabel *label_10;
    QFrame *line_8;
    QLabel *label_9;
    QFrame *line_7;
    QLabel *lbX;
    QFrame *line_9;
    QFrame *line_10;
    QLabel *lbY;
    QLabel *lbZ;
    QPushButton *btnDown;
    QPushButton *btnUp;
    QLabel *label_7;
    QLabel *label_3;
    QLineEdit *leZValue;
    QLineEdit *leYValue;
    QLineEdit *leXValue;
    QLabel *label;
    QLabel *label_2;
    QGroupBox *groupBox_3;
    QFrame *line_3;
    QFrame *line_4;
    QComboBox *cmbDivision;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *leVeloc;
    QLineEdit *leAccel;
    QPushButton *btnHoming;
    QGroupBox *gbConnection;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *btnSettingConnect;
    QPushButton *btnConnect;
    QWidget *tab3;
    QGroupBox *groupBox_7;
    QPushButton *btnLoadCam;
    QPushButton *btnCaptureImage;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_11;
    QLabel *label_12;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *leIDCam;
    QLineEdit *leFPS;
    QPushButton *btnStartProgram;
    QComboBox *cmbModeDisplay;
    QGroupBox *groupBox_8;
    QPushButton *btnShowObjectTrackingTable;
    QPushButton *btnClearAllObject;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_13;
    QLabel *label_14;
    QVBoxLayout *verticalLayout_5;
    QLabel *lbTrackingObjectNumber;
    QLabel *lbVisibleObjectNumber;
    QPushButton *btnGCodeView;
    QGroupBox *groupBox;
    QPushButton *btnLine;
    QPushButton *btnPoint;
    QPushButton *btnRectangle;
    QLineEdit *leRealDistance;
    QLineEdit *leXCoordinate;
    QLineEdit *leYCoordinate;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QPushButton *btnTransform;
    QPushButton *btnSaveSettings;
    QPushButton *btnLoadSettings;
    QGroupBox *grpCam;
    CameraWidget *lblCam;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(853, 523);
        MainWindow->setMinimumSize(QSize(853, 517));
        MainWindow->setMaximumSize(QSize(853, 528));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/mainwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setAutoFillBackground(true);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("QWidget{\n"
"background-color: rgb(248, 248, 248);\n"
"}"));
        verticalLayout_7 = new QVBoxLayout(centralwidget);
        verticalLayout_7->setObjectName("verticalLayout_7");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setTabletTracking(false);
        tabWidget->setFocusPolicy(Qt::TabFocus);
        tabWidget->setAcceptDrops(false);
        tabWidget->setAutoFillBackground(false);
        tabWidget->setStyleSheet(QString::fromUtf8(""));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Triangular);
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setDocumentMode(true);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(true);
        tabWidget->setTabBarAutoHide(false);
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        gridLayout = new QGridLayout(tab_2);
        gridLayout->setObjectName("gridLayout");
        label_16 = new QLabel(tab_2);
        label_16->setObjectName("label_16");
        label_16->setPixmap(QPixmap(QString::fromUtf8(":/icons/imgStart.jpg")));
        label_16->setScaledContents(true);

        gridLayout->addWidget(label_16, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab1 = new QWidget();
        tab1->setObjectName("tab1");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tab1->sizePolicy().hasHeightForWidth());
        tab1->setSizePolicy(sizePolicy);
        tab1->setFocusPolicy(Qt::TabFocus);
        tab1->setAutoFillBackground(false);
        tab1->setStyleSheet(QString::fromUtf8(""));
        groupBox_2 = new QGroupBox(tab1);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(220, 10, 161, 91));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(true);
        groupBox_2->setFont(font);
        groupBox_2->setAutoFillBackground(false);
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"	border:none;\n"
"	background-color: rgb(85, 255, 120);\n"
"	color: black;\n"
"	border-radius:10px;\n"
"	font: 700 12pt \"Segoe UI\";\n"
"}"));
        groupBox_2->setAlignment(Qt::AlignCenter);
        groupBox_2->setFlat(true);
        btnSetSpeedConveyor = new QPushButton(groupBox_2);
        btnSetSpeedConveyor->setObjectName("btnSetSpeedConveyor");
        btnSetSpeedConveyor->setGeometry(QRect(10, 60, 61, 21));
        btnSetSpeedConveyor->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	color: rgb(255, 255, 255);\n"
"	background-color:rgb(213, 85, 255);\n"
"	border-radius:5px;\n"
"	\n"
"	font: 12pt \"Segoe UI Semibold\";\n"
"	\n"
"}\n"
"\n"
"QPushButton:Hover\n"
"{\n"
"	background-color:rgb(255, 0, 0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:rgb(247, 221, 90);\n"
"}"));
        btnTurnOffConveyor = new QPushButton(groupBox_2);
        btnTurnOffConveyor->setObjectName("btnTurnOffConveyor");
        btnTurnOffConveyor->setGeometry(QRect(80, 30, 71, 22));
        btnTurnOffConveyor->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	color: rgb(255, 255, 255);\n"
"	background-color:rgb(213, 85, 255);\n"
"	border-radius:5px;\n"
"	\n"
"	font: 12pt \"Segoe UI Semibold\";\n"
"	\n"
"}\n"
"\n"
"QPushButton:Hover\n"
"{\n"
"	background-color:rgb(255, 0, 0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:rgb(247, 221, 90);\n"
"}"));
        btnTurnOnConveyor = new QPushButton(groupBox_2);
        btnTurnOnConveyor->setObjectName("btnTurnOnConveyor");
        btnTurnOnConveyor->setGeometry(QRect(10, 30, 60, 22));
        btnTurnOnConveyor->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	color: rgb(255, 255, 255);\n"
"	background-color:rgb(213, 85, 255);\n"
"	border-radius:5px;\n"
"	\n"
"	font: 12pt \"Segoe UI Semibold\";\n"
"	\n"
"}\n"
"\n"
"QPushButton:Hover\n"
"{\n"
"	background-color:rgb(255, 0, 0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:rgb(247, 221, 90);\n"
"}"));
        leSpeedConveyor = new QLineEdit(groupBox_2);
        leSpeedConveyor->setObjectName("leSpeedConveyor");
        leSpeedConveyor->setGeometry(QRect(80, 60, 71, 22));
        leSpeedConveyor->setStyleSheet(QString::fromUtf8("font: 9pt \"Segoe UI\";\n"
"background-color:none;\n"
""));
        leSpeedConveyor->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tabWidget_2 = new QTabWidget(tab1);
        tabWidget_2->setObjectName("tabWidget_2");
        tabWidget_2->setGeometry(QRect(390, 0, 431, 441));
        tab = new QWidget();
        tab->setObjectName("tab");
        tabWidget_2->addTab(tab, QString());
        t2D = new QWidget();
        t2D->setObjectName("t2D");
        groupBox_6 = new QGroupBox(t2D);
        groupBox_6->setObjectName("groupBox_6");
        groupBox_6->setGeometry(QRect(10, 10, 411, 391));
        groupBox_6->setFlat(true);
        groupBox_6->setCheckable(false);
        sldZAdjustion = new QSlider(groupBox_6);
        sldZAdjustion->setObjectName("sldZAdjustion");
        sldZAdjustion->setGeometry(QRect(9, 25, 22, 311));
        sldZAdjustion->setMaximum(300);
        sldZAdjustion->setValue(0);
        sldZAdjustion->setOrientation(Qt::Vertical);
        sldZAdjustion->setInvertedAppearance(true);
        wg2d = new QWidget(groupBox_6);
        wg2d->setObjectName("wg2d");
        wg2d->setEnabled(true);
        wg2d->setGeometry(QRect(50, 30, 370, 355));
        wg2d->setStyleSheet(QString::fromUtf8(""));
        btnVacuum = new QPushButton(groupBox_6);
        btnVacuum->setObjectName("btnVacuum");
        btnVacuum->setGeometry(QRect(0, 360, 41, 31));
        btnVacuum->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	border: none;\n"
"	background-color: none;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/off-button.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/icons/on-button.png"), QSize(), QIcon::Normal, QIcon::On);
        btnVacuum->setIcon(icon1);
        btnVacuum->setIconSize(QSize(30, 30));
        btnVacuum->setCheckable(true);
        label_15 = new QLabel(groupBox_6);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(0, 340, 41, 21));
        QFont font1;
        font1.setPointSize(8);
        label_15->setFont(font1);
        label_15->setStyleSheet(QString::fromUtf8("	background-color: none;"));
        tabWidget_2->addTab(t2D, QString());
        gbMotionControl = new QGroupBox(tab1);
        gbMotionControl->setObjectName("gbMotionControl");
        gbMotionControl->setGeometry(QRect(10, 110, 371, 221));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(gbMotionControl->sizePolicy().hasHeightForWidth());
        gbMotionControl->setSizePolicy(sizePolicy2);
        gbMotionControl->setFont(font);
        gbMotionControl->setFocusPolicy(Qt::NoFocus);
        gbMotionControl->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"	border:none;\n"
"	background-color: rgb(85, 255, 120);\n"
"	color: black;\n"
"	border-radius:10px;\n"
"	font: 700 12pt \"Segoe UI\";\n"
"}"));
        gbMotionControl->setFlat(false);
        gbMotionControl->setCheckable(false);
        btnGo = new QPushButton(gbMotionControl);
        btnGo->setObjectName("btnGo");
        btnGo->setGeometry(QRect(10, 30, 41, 31));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(btnGo->sizePolicy().hasHeightForWidth());
        btnGo->setSizePolicy(sizePolicy3);
        btnGo->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	color: rgb(255, 255, 255);\n"
"	background-color:rgb(213, 85, 255);\n"
"	border-radius:5px;\n"
"	\n"
"	font: 700 14pt \"Segoe UI\";\n"
"	\n"
"}\n"
"\n"
"QPushButton:Hover\n"
"{\n"
"	background-color:rgb(255, 0, 0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:rgb(247, 221, 90);\n"
"}"));
        btnForward = new QPushButton(gbMotionControl);
        btnForward->setObjectName("btnForward");
        btnForward->setGeometry(QRect(60, 90, 41, 24));
        btnForward->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	color: rgb(255, 255, 255);\n"
"	background-color:rgb(213, 85, 255);\n"
"	border-radius:5px;\n"
"	\n"
"	font: 700 13pt \"Segoe UI\";\n"
"	\n"
"}\n"
"\n"
"QPushButton:Hover\n"
"{\n"
"	background-color:rgb(255, 0, 0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:rgb(247, 221, 90);\n"
"}"));
        btnLeft = new QPushButton(gbMotionControl);
        btnLeft->setObjectName("btnLeft");
        btnLeft->setGeometry(QRect(10, 130, 41, 24));
        btnLeft->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	color: rgb(255, 255, 255);\n"
"	background-color:rgb(213, 85, 255);\n"
"	border-radius:5px;\n"
"	\n"
"	font: 700 13pt \"Segoe UI\";\n"
"	\n"
"}\n"
"\n"
"QPushButton:Hover\n"
"{\n"
"	background-color:rgb(255, 0, 0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:rgb(247, 221, 90);\n"
"}"));
        btnRight = new QPushButton(gbMotionControl);
        btnRight->setObjectName("btnRight");
        btnRight->setGeometry(QRect(110, 130, 42, 24));
        btnRight->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	color: rgb(255, 255, 255);\n"
"	background-color:rgb(213, 85, 255);\n"
"	border-radius:5px;\n"
"	\n"
"	font: 700 13pt \"Segoe UI\";\n"
"	\n"
"}\n"
"\n"
"QPushButton:Hover\n"
"{\n"
"	background-color:rgb(255, 0, 0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:rgb(247, 221, 90);\n"
"}"));
        btnBackward = new QPushButton(gbMotionControl);
        btnBackward->setObjectName("btnBackward");
        btnBackward->setGeometry(QRect(60, 170, 41, 24));
        btnBackward->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	color: rgb(255, 255, 255);\n"
"	background-color:rgb(213, 85, 255);\n"
"	border-radius:5px;\n"
"	\n"
"	font: 700 13pt \"Segoe UI\";\n"
"	\n"
"}\n"
"\n"
"QPushButton:Hover\n"
"{\n"
"	background-color:rgb(255, 0, 0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:rgb(247, 221, 90);\n"
"}"));
        groupBox_4 = new QGroupBox(gbMotionControl);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(220, 70, 131, 141));
        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(11, 107, 16, 21));
        label_8->setStyleSheet(QString::fromUtf8("\n"
"QLabel{font: 700 12pt \"Segoe UI\";\n"
"	background-color: none;\n"
"}"));
        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(11, 31, 16, 21));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy4);
        label_10->setStyleSheet(QString::fromUtf8("\n"
"QLabel{font: 700 12pt \"Segoe UI\";\n"
"	background-color: none;\n"
"}"));
        line_8 = new QFrame(groupBox_4);
        line_8->setObjectName("line_8");
        line_8->setGeometry(QRect(11, 98, 19, 16));
        line_8->setStyleSheet(QString::fromUtf8("background-color:none;"));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);
        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(11, 69, 16, 21));
        label_9->setStyleSheet(QString::fromUtf8("\n"
"QLabel{font: 700 12pt \"Segoe UI\";\n"
"	background-color: none;\n"
"}"));
        line_7 = new QFrame(groupBox_4);
        line_7->setObjectName("line_7");
        line_7->setGeometry(QRect(11, 60, 19, 16));
        line_7->setStyleSheet(QString::fromUtf8("background-color:none;"));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);
        lbX = new QLabel(groupBox_4);
        lbX->setObjectName("lbX");
        lbX->setGeometry(QRect(51, 31, 41, 21));
        sizePolicy4.setHeightForWidth(lbX->sizePolicy().hasHeightForWidth());
        lbX->setSizePolicy(sizePolicy4);
        lbX->setStyleSheet(QString::fromUtf8("QWidget{\n"
"background-color: none;\n"
"}"));
        line_9 = new QFrame(groupBox_4);
        line_9->setObjectName("line_9");
        line_9->setGeometry(QRect(51, 60, 39, 16));
        line_9->setStyleSheet(QString::fromUtf8("background-color:none;"));
        line_9->setFrameShape(QFrame::HLine);
        line_9->setFrameShadow(QFrame::Sunken);
        line_10 = new QFrame(groupBox_4);
        line_10->setObjectName("line_10");
        line_10->setGeometry(QRect(51, 98, 39, 16));
        line_10->setStyleSheet(QString::fromUtf8("background-color:none;"));
        line_10->setFrameShape(QFrame::HLine);
        line_10->setFrameShadow(QFrame::Sunken);
        lbY = new QLabel(groupBox_4);
        lbY->setObjectName("lbY");
        lbY->setGeometry(QRect(51, 69, 41, 21));
        lbY->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	background-color: none;\n"
"}"));
        lbZ = new QLabel(groupBox_4);
        lbZ->setObjectName("lbZ");
        lbZ->setGeometry(QRect(51, 107, 51, 21));
        lbZ->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	background-color: none;\n"
"}"));
        btnDown = new QPushButton(gbMotionControl);
        btnDown->setObjectName("btnDown");
        btnDown->setGeometry(QRect(150, 160, 42, 24));
        btnDown->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	color: rgb(255, 255, 255);\n"
"	background-color:rgb(213, 85, 255);\n"
"	border-radius:5px;\n"
"	\n"
"	font: 700 13pt \"Segoe UI\";\n"
"	\n"
"}\n"
"\n"
"QPushButton:Hover\n"
"{\n"
"	background-color:rgb(255, 0, 0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:rgb(247, 221, 90);\n"
"}"));
        btnUp = new QPushButton(gbMotionControl);
        btnUp->setObjectName("btnUp");
        btnUp->setGeometry(QRect(150, 100, 42, 24));
        btnUp->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	color: rgb(255, 255, 255);\n"
"	background-color:rgb(213, 85, 255);\n"
"	border-radius:5px;\n"
"	\n"
"	font: 700 13pt \"Segoe UI\";\n"
"	\n"
"}\n"
"\n"
"QPushButton:Hover\n"
"{\n"
"	background-color:rgb(255, 0, 0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:rgb(247, 221, 90);\n"
"}"));
        label_7 = new QLabel(gbMotionControl);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(60, 120, 41, 41));
        label_7->setMaximumSize(QSize(80, 80));
        label_7->setStyleSheet(QString::fromUtf8("\n"
"QLabel{\n"
"	background-color: none;\n"
"}"));
        label_7->setPixmap(QPixmap(QString::fromUtf8(":/icons/compass.png")));
        label_7->setScaledContents(true);
        label_3 = new QLabel(gbMotionControl);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(250, 30, 16, 21));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI")});
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setItalic(false);
        label_3->setFont(font2);
        label_3->setAutoFillBackground(false);
        label_3->setStyleSheet(QString::fromUtf8("\n"
"QLabel{font: 700 14pt \"Segoe UI\";\n"
"	background-color: none;\n"
"}"));
        label_3->setFrameShape(QFrame::NoFrame);
        label_3->setFrameShadow(QFrame::Plain);
        label_3->setMidLineWidth(0);
        label_3->setAlignment(Qt::AlignCenter);
        leZValue = new QLineEdit(gbMotionControl);
        leZValue->setObjectName("leZValue");
        leZValue->setGeometry(QRect(270, 30, 61, 22));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(leZValue->sizePolicy().hasHeightForWidth());
        leZValue->setSizePolicy(sizePolicy5);
        leZValue->setStyleSheet(QString::fromUtf8("background-color:none;"));
        leYValue = new QLineEdit(gbMotionControl);
        leYValue->setObjectName("leYValue");
        leYValue->setGeometry(QRect(180, 30, 61, 22));
        leYValue->setStyleSheet(QString::fromUtf8("background-color:none;"));
        leXValue = new QLineEdit(gbMotionControl);
        leXValue->setObjectName("leXValue");
        leXValue->setGeometry(QRect(90, 30, 61, 22));
        leXValue->setStyleSheet(QString::fromUtf8("background-color:none;"));
        label = new QLabel(gbMotionControl);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 30, 16, 21));
        label->setFont(font2);
        label->setStyleSheet(QString::fromUtf8("\n"
"\n"
"QLabel{font: 700 14pt \"Segoe UI\";\n"
"	background-color: none;\n"
"}"));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(gbMotionControl);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(160, 30, 21, 21));
        label_2->setFont(font2);
        label_2->setStyleSheet(QString::fromUtf8("\n"
"QLabel{font: 700 14pt \"Segoe UI\";\n"
"	background-color: none;\n"
"}"));
        label_2->setAlignment(Qt::AlignCenter);
        groupBox_3 = new QGroupBox(tab1);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(9, 341, 371, 101));
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        groupBox_3->setFont(font);
        groupBox_3->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"	border:none;\n"
"	background-color: rgb(85, 255, 120);\n"
"	color: black;\n"
"	border-radius:10px;\n"
"	font: 700 12pt \"Segoe UI\";\n"
"}"));
        line_3 = new QFrame(groupBox_3);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(100, 30, 16, 61));
        line_3->setStyleSheet(QString::fromUtf8("background-color:none;"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(groupBox_3);
        line_4->setObjectName("line_4");
        line_4->setGeometry(QRect(223, 30, 16, 61));
        line_4->setStyleSheet(QString::fromUtf8("background-color:none;"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        cmbDivision = new QComboBox(groupBox_3);
        cmbDivision->addItem(QString());
        cmbDivision->addItem(QString());
        cmbDivision->addItem(QString());
        cmbDivision->addItem(QString());
        cmbDivision->addItem(QString());
        cmbDivision->setObjectName("cmbDivision");
        cmbDivision->setGeometry(QRect(11, 60, 71, 22));
        cmbDivision->setLayoutDirection(Qt::RightToLeft);
        cmbDivision->setStyleSheet(QString::fromUtf8("QComboBox{\n"
"background-color:white;\n"
"}"));
        cmbDivision->setInputMethodHints(Qt::ImhNone);
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(11, 30, 75, 20));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy6);
        label_4->setStyleSheet(QString::fromUtf8("\n"
"\n"
"QLabel{font: 700 11pt \"Segoe UI\";\n"
"	background-color: none;\n"
"}"));
        label_4->setFrameShape(QFrame::NoFrame);
        label_4->setLineWidth(1);
        label_4->setMidLineWidth(0);
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(110, 30, 113, 20));
        sizePolicy6.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy6);
        label_5->setStyleSheet(QString::fromUtf8("\n"
"QLabel{font: 700 11pt \"Segoe UI\";\n"
"	background-color: none;\n"
"}"));
        label_5->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(240, 30, 104, 20));
        sizePolicy6.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy6);
        label_6->setStyleSheet(QString::fromUtf8("\n"
"QLabel{font: 700 11pt \"Segoe UI\";\n"
"	background-color: none;\n"
"}"));
        label_6->setAlignment(Qt::AlignCenter);
        leVeloc = new QLineEdit(groupBox_3);
        leVeloc->setObjectName("leVeloc");
        leVeloc->setGeometry(QRect(120, 60, 91, 22));
        leVeloc->setStyleSheet(QString::fromUtf8("background-color:none;"));
        leVeloc->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        leAccel = new QLineEdit(groupBox_3);
        leAccel->setObjectName("leAccel");
        leAccel->setGeometry(QRect(240, 60, 91, 22));
        leAccel->setStyleSheet(QString::fromUtf8("background-color:none;"));
        leAccel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        btnHoming = new QPushButton(tab1);
        btnHoming->setObjectName("btnHoming");
        btnHoming->setGeometry(QRect(130, 20, 81, 81));
        sizePolicy.setHeightForWidth(btnHoming->sizePolicy().hasHeightForWidth());
        btnHoming->setSizePolicy(sizePolicy);
        QFont font3;
        font3.setPointSize(11);
        btnHoming->setFont(font3);
        btnHoming->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	border-radius:15px;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:rgb(255, 0, 0);\n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/house.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnHoming->setIcon(icon2);
        btnHoming->setIconSize(QSize(70, 70));
        gbConnection = new QGroupBox(tab1);
        gbConnection->setObjectName("gbConnection");
        gbConnection->setGeometry(QRect(10, 10, 111, 91));
        gbConnection->setFont(font);
        gbConnection->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"	border:none;\n"
"	background-color: rgb(85, 255, 120);\n"
"	color: black;\n"
"	border-radius:10px;\n"
"	font: 700 12pt \"Segoe UI\";\n"
"}"));
        gbConnection->setAlignment(Qt::AlignCenter);
        gbConnection->setFlat(true);
        widget = new QWidget(gbConnection);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 20, 111, 61));
        widget->setStyleSheet(QString::fromUtf8("background-color:none;"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(-1, 4, -1, 1);
        btnSettingConnect = new QPushButton(widget);
        btnSettingConnect->setObjectName("btnSettingConnect");
        QSizePolicy sizePolicy7(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(btnSettingConnect->sizePolicy().hasHeightForWidth());
        btnSettingConnect->setSizePolicy(sizePolicy7);
        btnSettingConnect->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	color: rgb(255, 255, 255);\n"
"	background-color:rgb(213, 85, 255);\n"
"	border-radius:5px;\n"
"	font: italic 11pt \"Segoe UI\";\n"
"}\n"
"\n"
"QPushButton:Hover\n"
"{\n"
"	background-color:rgb(255, 0, 0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:rgb(247, 221, 90);\n"
"}"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/setting.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSettingConnect->setIcon(icon3);

        verticalLayout->addWidget(btnSettingConnect);

        btnConnect = new QPushButton(widget);
        btnConnect->setObjectName("btnConnect");
        sizePolicy.setHeightForWidth(btnConnect->sizePolicy().hasHeightForWidth());
        btnConnect->setSizePolicy(sizePolicy);
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Segoe UI")});
        font4.setPointSize(12);
        font4.setBold(true);
        font4.setItalic(false);
        btnConnect->setFont(font4);
        btnConnect->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:none;\n"
"	color: rgb(255, 255, 255);\n"
"	background-color:rgb(213, 85, 255);\n"
"	border-radius:5px;\n"
"}\n"
"\n"
"QPushButton:Hover\n"
"{\n"
"	background-color:rgb(255, 0, 0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:rgb(247, 221, 90);\n"
"}"));

        verticalLayout->addWidget(btnConnect);

        tabWidget->addTab(tab1, QString());
        tab3 = new QWidget();
        tab3->setObjectName("tab3");
        groupBox_7 = new QGroupBox(tab3);
        groupBox_7->setObjectName("groupBox_7");
        groupBox_7->setGeometry(QRect(10, 10, 231, 91));
        btnLoadCam = new QPushButton(groupBox_7);
        btnLoadCam->setObjectName("btnLoadCam");
        btnLoadCam->setGeometry(QRect(10, 20, 71, 61));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/webcam_on.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon4.addFile(QString::fromUtf8(":/icons/webcam_off.png"), QSize(), QIcon::Normal, QIcon::On);
        btnLoadCam->setIcon(icon4);
        btnLoadCam->setIconSize(QSize(50, 50));
        btnLoadCam->setCheckable(true);
        btnCaptureImage = new QPushButton(groupBox_7);
        btnCaptureImage->setObjectName("btnCaptureImage");
        btnCaptureImage->setGeometry(QRect(160, 30, 61, 41));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/photography.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnCaptureImage->setIcon(icon5);
        btnCaptureImage->setIconSize(QSize(30, 30));
        layoutWidget = new QWidget(groupBox_7);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(91, 21, 24, 61));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName("label_11");

        verticalLayout_2->addWidget(label_11);

        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName("label_12");

        verticalLayout_2->addWidget(label_12);

        layoutWidget1 = new QWidget(groupBox_7);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(121, 21, 32, 61));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        leIDCam = new QLineEdit(layoutWidget1);
        leIDCam->setObjectName("leIDCam");
        QSizePolicy sizePolicy8(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(leIDCam->sizePolicy().hasHeightForWidth());
        leIDCam->setSizePolicy(sizePolicy8);
        leIDCam->setMaximumSize(QSize(30, 25));

        verticalLayout_3->addWidget(leIDCam);

        leFPS = new QLineEdit(layoutWidget1);
        leFPS->setObjectName("leFPS");
        sizePolicy8.setHeightForWidth(leFPS->sizePolicy().hasHeightForWidth());
        leFPS->setSizePolicy(sizePolicy8);
        leFPS->setMaximumSize(QSize(30, 25));

        verticalLayout_3->addWidget(leFPS);

        btnStartProgram = new QPushButton(tab3);
        btnStartProgram->setObjectName("btnStartProgram");
        btnStartProgram->setGeometry(QRect(740, 390, 81, 71));
        btnStartProgram->setAutoFillBackground(false);
        btnStartProgram->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border-radius:15px;\n"
"	background-color:rgb(199, 255, 115);\n"
"}\n"
""));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon6.addFile(QString::fromUtf8(":/icons/stop-button.png"), QSize(), QIcon::Normal, QIcon::On);
        btnStartProgram->setIcon(icon6);
        btnStartProgram->setIconSize(QSize(65, 65));
        btnStartProgram->setCheckable(true);
        cmbModeDisplay = new QComboBox(tab3);
        cmbModeDisplay->addItem(QString());
        cmbModeDisplay->addItem(QString());
        cmbModeDisplay->addItem(QString());
        cmbModeDisplay->addItem(QString());
        cmbModeDisplay->setObjectName("cmbModeDisplay");
        cmbModeDisplay->setGeometry(QRect(730, 10, 91, 22));
        cmbModeDisplay->setLayoutDirection(Qt::LeftToRight);
        groupBox_8 = new QGroupBox(tab3);
        groupBox_8->setObjectName("groupBox_8");
        groupBox_8->setGeometry(QRect(10, 110, 141, 131));
        btnShowObjectTrackingTable = new QPushButton(groupBox_8);
        btnShowObjectTrackingTable->setObjectName("btnShowObjectTrackingTable");
        btnShowObjectTrackingTable->setGeometry(QRect(14, 20, 111, 24));
        btnClearAllObject = new QPushButton(groupBox_8);
        btnClearAllObject->setObjectName("btnClearAllObject");
        btnClearAllObject->setGeometry(QRect(14, 50, 111, 24));
        layoutWidget2 = new QWidget(groupBox_8);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(20, 80, 101, 42));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_13 = new QLabel(layoutWidget2);
        label_13->setObjectName("label_13");

        verticalLayout_4->addWidget(label_13);

        label_14 = new QLabel(layoutWidget2);
        label_14->setObjectName("label_14");

        verticalLayout_4->addWidget(label_14);


        horizontalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        lbTrackingObjectNumber = new QLabel(layoutWidget2);
        lbTrackingObjectNumber->setObjectName("lbTrackingObjectNumber");
        lbTrackingObjectNumber->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(lbTrackingObjectNumber);

        lbVisibleObjectNumber = new QLabel(layoutWidget2);
        lbVisibleObjectNumber->setObjectName("lbVisibleObjectNumber");
        lbVisibleObjectNumber->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(lbVisibleObjectNumber);


        horizontalLayout_2->addLayout(verticalLayout_5);

        btnGCodeView = new QPushButton(tab3);
        btnGCodeView->setObjectName("btnGCodeView");
        btnGCodeView->setGeometry(QRect(630, 430, 101, 31));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/letter-g.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnGCodeView->setIcon(icon7);
        btnGCodeView->setIconSize(QSize(20, 20));
        groupBox = new QGroupBox(tab3);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 250, 251, 111));
        btnLine = new QPushButton(groupBox);
        btnLine->setObjectName("btnLine");
        btnLine->setGeometry(QRect(10, 20, 91, 24));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/measure.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnLine->setIcon(icon8);
        btnLine->setCheckable(true);
        btnPoint = new QPushButton(groupBox);
        btnPoint->setObjectName("btnPoint");
        btnPoint->setGeometry(QRect(10, 50, 91, 24));
        btnPoint->setLayoutDirection(Qt::LeftToRight);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/graph.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPoint->setIcon(icon9);
        btnPoint->setCheckable(true);
        btnRectangle = new QPushButton(groupBox);
        btnRectangle->setObjectName("btnRectangle");
        btnRectangle->setGeometry(QRect(10, 80, 91, 24));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icons/frame.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnRectangle->setIcon(icon10);
        btnRectangle->setCheckable(true);
        leRealDistance = new QLineEdit(groupBox);
        leRealDistance->setObjectName("leRealDistance");
        leRealDistance->setGeometry(QRect(130, 20, 41, 22));
        leXCoordinate = new QLineEdit(groupBox);
        leXCoordinate->setObjectName("leXCoordinate");
        leXCoordinate->setGeometry(QRect(130, 50, 41, 22));
        leYCoordinate = new QLineEdit(groupBox);
        leYCoordinate->setObjectName("leYCoordinate");
        leYCoordinate->setGeometry(QRect(200, 50, 41, 22));
        label_17 = new QLabel(groupBox);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(190, 21, 41, 21));
        label_17->setFont(font3);
        label_18 = new QLabel(groupBox);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(120, 50, 16, 21));
        label_18->setFont(font3);
        label_19 = new QLabel(groupBox);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(190, 50, 16, 21));
        label_19->setFont(font3);
        btnTransform = new QPushButton(groupBox);
        btnTransform->setObjectName("btnTransform");
        btnTransform->setGeometry(QRect(130, 80, 61, 24));
        btnTransform->setCheckable(true);
        btnSaveSettings = new QPushButton(groupBox);
        btnSaveSettings->setObjectName("btnSaveSettings");
        btnSaveSettings->setGeometry(QRect(200, 80, 21, 24));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8("icons/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSaveSettings->setIcon(icon11);
        btnLoadSettings = new QPushButton(groupBox);
        btnLoadSettings->setObjectName("btnLoadSettings");
        btnLoadSettings->setGeometry(QRect(220, 80, 21, 24));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8("icons/file.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnLoadSettings->setIcon(icon12);
        label_18->raise();
        label_19->raise();
        btnLine->raise();
        btnPoint->raise();
        btnRectangle->raise();
        leRealDistance->raise();
        leXCoordinate->raise();
        leYCoordinate->raise();
        label_17->raise();
        btnTransform->raise();
        btnSaveSettings->raise();
        btnLoadSettings->raise();
        grpCam = new QGroupBox(tab3);
        grpCam->setObjectName("grpCam");
        grpCam->setGeometry(QRect(300, 40, 521, 321));
        lblCam = new CameraWidget(grpCam);
        lblCam->setObjectName("lblCam");
        lblCam->setGeometry(QRect(10, 10, 500, 300));
        lblCam->setCursor(QCursor(Qt::PointingHandCursor));
        tabWidget->addTab(tab3, QString());

        verticalLayout_7->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Delta Robot UI", nullptr));
        label_16->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "              Hello World                ", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Conveyor", nullptr));
        btnSetSpeedConveyor->setText(QCoreApplication::translate("MainWindow", "Speed", nullptr));
        btnTurnOffConveyor->setText(QCoreApplication::translate("MainWindow", "Turn off", nullptr));
        btnTurnOnConveyor->setText(QCoreApplication::translate("MainWindow", "Turn on", nullptr));
#if QT_CONFIG(accessibility)
        leSpeedConveyor->setAccessibleDescription(QString());
#endif // QT_CONFIG(accessibility)
        leSpeedConveyor->setInputMask(QString());
        leSpeedConveyor->setText(QCoreApplication::translate("MainWindow", "200", nullptr));
        leSpeedConveyor->setPlaceholderText(QCoreApplication::translate("MainWindow", "mm/s", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab), QCoreApplication::translate("MainWindow", "3D", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "2D Mode", nullptr));
        btnVacuum->setText(QString());
        label_15->setText(QCoreApplication::translate("MainWindow", "Vacuum", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(t2D), QCoreApplication::translate("MainWindow", "2D", nullptr));
        gbMotionControl->setTitle(QCoreApplication::translate("MainWindow", "Motion control", nullptr));
        btnGo->setText(QCoreApplication::translate("MainWindow", "Go", nullptr));
        btnForward->setText(QCoreApplication::translate("MainWindow", "F", nullptr));
        btnLeft->setText(QCoreApplication::translate("MainWindow", "L", nullptr));
        btnRight->setText(QCoreApplication::translate("MainWindow", "R", nullptr));
        btnBackward->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Coordinates", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Z:", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        lbX->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        lbY->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        lbZ->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        btnDown->setText(QCoreApplication::translate("MainWindow", "D", nullptr));
        btnUp->setText(QCoreApplication::translate("MainWindow", "U", nullptr));
        label_7->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Properties", nullptr));
        cmbDivision->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        cmbDivision->setItemText(1, QCoreApplication::translate("MainWindow", "5", nullptr));
        cmbDivision->setItemText(2, QCoreApplication::translate("MainWindow", "10", nullptr));
        cmbDivision->setItemText(3, QCoreApplication::translate("MainWindow", "50", nullptr));
        cmbDivision->setItemText(4, QCoreApplication::translate("MainWindow", "100", nullptr));

        label_4->setText(QCoreApplication::translate("MainWindow", "Step (mm)", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Veloc (mm/s)", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Accel (mm/s2)", nullptr));
        leVeloc->setText(QCoreApplication::translate("MainWindow", "200", nullptr));
        leAccel->setText(QCoreApplication::translate("MainWindow", "1200", nullptr));
        btnHoming->setText(QString());
        gbConnection->setTitle(QCoreApplication::translate("MainWindow", "Connection", nullptr));
        btnSettingConnect->setText(QCoreApplication::translate("MainWindow", "Setting", nullptr));
        btnConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QCoreApplication::translate("MainWindow", "            Control Robot              ", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("MainWindow", "Camera", nullptr));
        btnLoadCam->setText(QString());
        btnCaptureImage->setText(QString());
        label_11->setText(QCoreApplication::translate("MainWindow", "ID:", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "FPS:", nullptr));
        leIDCam->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        leFPS->setText(QCoreApplication::translate("MainWindow", "15", nullptr));
        btnStartProgram->setText(QString());
        cmbModeDisplay->setItemText(0, QCoreApplication::translate("MainWindow", "Normal", nullptr));
        cmbModeDisplay->setItemText(1, QCoreApplication::translate("MainWindow", "Processing", nullptr));
        cmbModeDisplay->setItemText(2, QCoreApplication::translate("MainWindow", "Calibration", nullptr));
        cmbModeDisplay->setItemText(3, QCoreApplication::translate("MainWindow", "Result", nullptr));

        groupBox_8->setTitle(QCoreApplication::translate("MainWindow", "Observing Object", nullptr));
        btnShowObjectTrackingTable->setText(QCoreApplication::translate("MainWindow", "Object table", nullptr));
        btnClearAllObject->setText(QCoreApplication::translate("MainWindow", "Clear Object", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Tracking", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Visible", nullptr));
        lbTrackingObjectNumber->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        lbVisibleObjectNumber->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        btnGCodeView->setText(QCoreApplication::translate("MainWindow", "GCode View", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Measurement", nullptr));
        btnLine->setText(QCoreApplication::translate("MainWindow", " Line         ", nullptr));
        btnPoint->setText(QCoreApplication::translate("MainWindow", " Point       ", nullptr));
        btnRectangle->setText(QCoreApplication::translate("MainWindow", "Rectangle", nullptr));
        leRealDistance->setText(QCoreApplication::translate("MainWindow", "100", nullptr));
        leXCoordinate->setText(QCoreApplication::translate("MainWindow", "50", nullptr));
        leYCoordinate->setText(QCoreApplication::translate("MainWindow", "-150", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "mm", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        btnTransform->setText(QCoreApplication::translate("MainWindow", "Transform", nullptr));
        btnSaveSettings->setText(QString());
        btnLoadSettings->setText(QString());
        grpCam->setTitle(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab3), QCoreApplication::translate("MainWindow", "            Image Processing           ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
