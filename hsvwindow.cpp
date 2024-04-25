#include "hsvwindow.h"
#include "ui_hsvwindow.h"
#include <QDebug>

HSVWindow::HSVWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HSVWindow)
{
    ui->setupUi(this);
    
    setGeometry(250, 145, 329, 319);


    initVariables();
    initEvents();
}

HSVWindow::~HSVWindow()
{
    delete ui;
}

void HSVWindow::initEvents()
{
    connect(ui->btnObject1, SIGNAL(clicked()), this, SLOT(addObject1()));
    connect(ui->btnObject2, SIGNAL(clicked()), this, SLOT(addObject2()));
    connect(ui->btnObject3, SIGNAL(clicked()), this, SLOT(addObject3()));

    for(int i=0; i<6; i++){
        connect(sliderWidget[i], SIGNAL(valueChanged(int)), this, SLOT(updateSliderValue()));
    }
}

void HSVWindow::initVariables()
{
    sliderWidget[0] = ui->sldMinH;
    sliderWidget[1] = ui->sldMaxH;
    sliderWidget[2] = ui->sldMinS;
    sliderWidget[3] = ui->sldMaxS;
    sliderWidget[4] = ui->sldMinV;
    sliderWidget[5] = ui->sldMaxV;

    lblSliderValue[0] = ui->lblMinH;
    lblSliderValue[1] = ui->lblMaxH;
    lblSliderValue[2] = ui->lblMinS;
    lblSliderValue[3] = ui->lblMaxS;
    lblSliderValue[4] = ui->lblMinV;
    lblSliderValue[5] = ui->lblMaxV;
}

void HSVWindow::addObject1()
{
    QString nameObject = ui->leObject1Name->text();
    emit addObject(1, nameObject);
}

void HSVWindow::addObject2()
{
    QString nameObject = ui->leObject2Name->text();
    emit addObject(2, nameObject);
}

void HSVWindow::addObject3()
{
    QString nameObject = ui->leObject3Name->text();
    emit addObject(3, nameObject);
}

void HSVWindow::updateSliderValue()
{

    for(int i=0; i<6; i++){
        lblSliderValue[i]->setText(QString::number(sliderWidget[i]->value()));
    }

    emit valueChanged(sliderWidget[0]->value(),sliderWidget[1]->value(), sliderWidget[2]->value(), sliderWidget[3]->value(),
                      sliderWidget[4]->value(), sliderWidget[5]->value() );
}
