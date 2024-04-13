#ifndef OBJECTVARIABLETABLE_H
#define OBJECTVARIABLETABLE_H

#include <QObject>
#include <QLabel>
#include <QGridLayout>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class ObjectVariable{
public:
    ObjectVariable(int i){

        QFont fontName = QFont();
        fontName.setBold(true);

        QFont fontVar = QFont();
        fontVar.setPointSize(10);

        QFont fontValue = QFont();
        fontValue.setItalic(true);

        name = new QLabel(QString("Object ") + QString::number(i+1) + " -");
        name->setFont(fontName);

        xVar = new QLabel(QString(" #O") + QString::number(i+1) + "_X: ");
        xVar->setFont(fontVar);
        xValue = new QLabel();
        xValue->setFont(fontValue);

        yVar = new QLabel(QString(" #O") + QString::number(i+1) + "_Y: ");
        yVar->setFont(fontVar);
        yValue = new QLabel();
        yValue->setFont(fontValue);

        aVar = new QLabel(QString(" #O") + QString::number(i+1) + "_A: ");
        aVar->setFont(fontVar);
        aValue = new QLabel();
        aValue->setFont(fontValue);

    }
    ~ObjectVariable(){
        delete name;
        delete xVar;
        delete xValue;
        delete yVar;
        delete yValue;
        delete aVar;
        delete aValue;
    }

    void addLayout(QGridLayout* layout, int row){
        this->layout = layout;

        layout->addWidget(name, row, 0);
        layout->addWidget(xVar, row, 1);
        layout->addWidget(xValue, row, 2);
        layout->addWidget(yVar, row, 3);
        layout->addWidget(yValue, row, 4);
        layout->addWidget(aVar, row, 5);
        layout->addWidget(aValue, row, 6);

    }

    QGridLayout *layout;

    QLabel *name;
    QLabel *xVar;
    QLabel *xValue;
    QLabel *yVar;
    QLabel *yValue;
    QLabel *aVar;
    QLabel *aValue;

};


class ObjectVariableTable : public QObject
{
    Q_OBJECT
public:
    explicit ObjectVariableTable(QObject *parent = nullptr);
    ~ObjectVariableTable();

public slots:
    void displayDialog();
    void updateTable(std::vector<cv::RotatedRect> objectContainer);

signals:

private:
    QWidget *dialog;
    QGridLayout *gridLayout;
    QList<ObjectVariable*> *objectVariableWidgetList;
};

#endif // OBJECTVARIABLETABLE_H
