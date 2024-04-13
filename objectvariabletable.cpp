#include "objectvariabletable.h"
#include <QDebug>

ObjectVariableTable::ObjectVariableTable(QObject *parent)
    : QObject{parent}
{
    objectVariableWidgetList = new QList<ObjectVariable*>();

    dialog = new QWidget();
    dialog->setWindowTitle("Object Variables");
    gridLayout = new QGridLayout();
    dialog->setLayout(gridLayout);

    dialog->setWindowFlag(Qt::WindowStaysOnTopHint);

}

ObjectVariableTable::~ObjectVariableTable()
{

}

void ObjectVariableTable::displayDialog()
{
    dialog->show();
}

void ObjectVariableTable::updateTable(std::vector<cv::RotatedRect> objectContainer)
{
    for(int i=0; i<objectContainer.size(); i++){
        if( i > objectVariableWidgetList->size() - 1){
            ObjectVariable *ov = new ObjectVariable(i);

            objectVariableWidgetList->push_back(ov);

            ov->addLayout(gridLayout, i);
        }
    }

    for(int i=0; i<objectContainer.size(); i++){
        objectVariableWidgetList->at(i)->xValue->setText(QString::number(objectContainer.at(i).center.x));
        objectVariableWidgetList->at(i)->yValue->setText(QString::number(objectContainer.at(i).center.y));

        int angle = 180;

        objectVariableWidgetList->at(i)->aValue->setText(QString::number(angle));
    }

    while (objectContainer.size() < objectVariableWidgetList->size()) {
        delete objectVariableWidgetList->last();
        objectVariableWidgetList->removeLast();
    }

}
