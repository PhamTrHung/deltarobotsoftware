#include "gcodewindow.h"
#include "ui_gcodewindow.h"

GCodeWindow::GCodeWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GCodeWindow)
{
    ui->setupUi(this);

    teGcodeWidget = ui->teGcode;
    btnLoadNewGcodeLine = ui->btnAddGcode;
    cmbProgramList = ui->cmbProgramList;

    connect(ui->btnAddGcode, SIGNAL(clicked(bool)), this, SLOT(addGcodeLine()));
    connect(ui->teGcode, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    connect(ui->btnSaveGcodeTe, SIGNAL(clicked(bool)), this, SIGNAL(saveGcodeInEditorToFile()));
    connect(ui->cmbProgramList, SIGNAL(currentIndexChanged(int)), this, SIGNAL(loadProgram()));
    connect(ui->btnFormat, SIGNAL(clicked(bool)), this, SLOT(formatGcodeText()));

}

GCodeWindow::~GCodeWindow()
{
    delete ui;
}

void GCodeWindow::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if(!ui->teGcode->isReadOnly()){
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = ui->teGcode->textCursor();
        selection.cursor.clearSelection();

        extraSelections.append(selection);
    }

    ui->teGcode->setExtraSelections(extraSelections);
}

void GCodeWindow::formatGcodeText()
{
    QString editorText = ui->teGcode->toPlainText();
    if(editorText.isEmpty()) return;

    QList<QString> lines = editorText.split('\n');
    QList<QString> newNumbers;
    QList<QString> oldNumbers;

    QString oldNumber = "";

    int i = 0;
    editorText = "";

    foreach (QString line, lines) {
        if(line == "") continue;
        line = line.replace("  ", " ");
        oldNumber = "";

        while(1){
            if(line[0] == ' '){
                line.replace(" ", "");
            }else{
                break;
            }
        }

        if(line[0] == 'N'){
            int spacePos = line.indexOf(' ');
            QString mS = line.mid(0, spacePos + 1);
            oldNumber = line.mid(1, spacePos);

            line.replace(mS, "");
        }

        while(1){
            if(line[0] == ' '){
                line.replace(" ", "");
            }else{
                break;
            }
        }

        if(line != ""){
            if(line[0] != ';'){
                QString numberS = QString("N") + QString::number(i);
                newNumbers.push_back(QString::number(i));
                oldNumbers.push_back(oldNumber);
                line = numberS + " " + line;
            }else{
                editorText += "\n" + line + "\n";
                continue;
            }
        }

        editorText += line + "\n";
        i += 5;
    }

    int gotoCursor = 0;
    gotoCursor = editorText.indexOf("GOTO");

    while(gotoCursor > -1){
        QString gotoIndexS = "";
        for(int i = 0; i < 20; ++i){
            QChar c  = editorText.at(gotoCursor + 5 + i);
            if(c.isDigit()) gotoIndexS += c;
            else break;
        }

        gotoCursor = editorText.indexOf("GOTO", gotoCursor + 5);

        for(int i = 0 ; i < oldNumbers.size(); ++i){
            if(oldNumbers.at(i).toInt() == gotoIndexS.toInt()){
                QString old = QString("GOTO ") + gotoIndexS;
                QString replace = QString("GOTO ") + newNumbers.at(i);
                editorText.replace(old, replace);
            }
        }

    }

    ui->teGcode->setPlainText(editorText);
}

void GCodeWindow::addGcodeLine()
{
    QString gcodeName = ui->cmbGcodeCmd->currentText();

    QString xValue = ui->leXValue->text() != "" ? (QString(" ") + ui->lbX->text() + ui->leXValue->text()) : "";
    QString yValue = ui->leYValue->text() != "" ? (QString(" ") + ui->lbY->text() + ui->leYValue->text()) : "";
    QString zValue = ui->leZValue->text() != "" ? (QString(" ") + ui->lbZ->text() + ui->leZValue->text()) : "";
    QString vValue = ui->leVValue->text() != "" ? (QString(" ") + ui->lbV->text() + ui->leVValue->text()) : "";
    QString aValue = ui->leAValue->text() != "" ? (QString(" ") + ui->lbA->text() + ui->leAValue->text()) : "";

    emit addNewGcodeLine(gcodeName + xValue + yValue + zValue + vValue + aValue);
}
